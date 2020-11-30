#include "Service.h"
#include <iostream>
#include <vector>
#include <QtCore\qlogging.h>

std::vector<Idea> Service::getAllIdeas()
{
	std::vector<Idea> idea = this->ideas.getAll();
	std::sort(idea.begin(), idea.end(), [](const Idea& a, const Idea& b){return (a.getAct() < b.getAct()); });
	/*for (int index1 = 0; index1 < idea.size() - 1; index1++)
		for (int index2 = index1 + 1; index2 < idea.size(); index2++)
			if (idea[index1].getAct() < idea[index2].getAct())
				std::swap(idea[index1], idea[index2]);*/
	return idea;
}

void Service::addIdea(std::string description, std::string creator, int act)
{
	if (act != 1 && act != 2 && act != 3)
		throw ValidationException("Invalid act!");
	this->ideas.add(Idea{ description, "proposed", creator, act });
	this->notify();
}

void Service::reviseIdea(std::string description, std::string writer, int act)
{
	std::vector<Idea> ideas = this->ideas.getAll();
	auto idea = std::find(ideas.begin(), ideas.end(), Idea{ description, "proposed", writer, act });
	if (idea != ideas.end())
	{
		if (idea->getStatus() == "proposed")
		{
			this->ideas.update(Idea{ description, "accepted", writer, act });
			this->notify();
		}
	}
}
