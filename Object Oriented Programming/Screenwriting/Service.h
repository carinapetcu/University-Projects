#pragma once
#include "Repository.h"
#include "Observer.h"
#include "Domain.h"
#include "Exceptions.h"
#include <string>
#include <vector>
#include <memory>
//#include "Observer.h"

class Service: public Subject
{
private:
	Repository<Idea>& ideas;

public:
	Service(Repository<Idea>& ideasNew) : ideas{ ideasNew }{};
	~Service() {};

	std::vector<Idea> getAllIdeas();
	void addIdea(std::string description, std::string creator, int act);
	void reviseIdea(std::string description, std::string writer, int act);

};