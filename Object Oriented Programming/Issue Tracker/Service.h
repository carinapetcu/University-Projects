#pragma once
#include "Repository.h"
#include "Observer.h"
#include "Domain.h"
#include <string>
#include <vector>
#include <memory>

class Service: public Subject
{
private:
	Repository<Issue>& issues;

public:
	Service(Repository<Issue>& issuesNew) : issues{ issuesNew } {};
	~Service() {};

	std::vector<Issue> getAllIssues();
	void addIssue(std::string description, std::string reporter);
	void removeIssue(std::string description);
	void resolveIssue(std::string description, std::string solver);
};