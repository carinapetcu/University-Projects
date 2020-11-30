#include "Service.h"
#include "Exceptions.h"
#include <iostream>

std::vector<Issue> Service::getAllIssues()
{
	std::vector<Issue> issues = this->issues.getAll();
	for (int index1 = 0; index1 < issues.size() - 1; index1++)
		for (int index2 = index1 + 1; index2 < issues.size(); index2++)
			if (issues[index1].getStatus() == issues[index2].getStatus())
			{
				if (issues[index1].getDescription() > issues[index2].getDescription())
					std::swap(issues[index1], issues[index2]);
			} else if(issues[index1].getStatus() < issues[index2].getStatus())
				std::swap(issues[index1], issues[index2]);
	return issues;
}

void Service::addIssue(std::string description, std::string reporter)
{
	Issue newIssue{ description, "open", reporter, "no solver" };
	this->issues.add(newIssue);
	this->notify();
}

void Service::removeIssue(std::string description)
{
	std::vector<Issue> issues = this->issues.getAll();
	for (auto issue : issues)
		if (issue.getDescription() == description)
		{
			if (issue.getStatus() == "closed")
			{
				Issue issueToUpdate{ description, "closed", issue.getReporter(), issue.getSolver() };
				this->issues.deleteElement(issueToUpdate);
				this->notify();
			}
			else
			{
				throw ServiceException("The issue is opened!");
			}
		}
}

void Service::resolveIssue(std::string description, std::string solver)
{
	std::vector<Issue> issues = this->issues.getAll();
	for(auto issue: issues)
		if (issue.getDescription() == description) 
		{
			if (issue.getStatus() == "open")
			{
				Issue issueToUpdate{ description, "closed", issue.getReporter(), solver };
				this->issues.update(issueToUpdate);
				this->notify();
			}
			else
			{
				throw ServiceException("The issue is already closed!");
			}
		}
}