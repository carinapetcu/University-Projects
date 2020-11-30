#pragma once
#include "Repository.h"
#include "Observer.h"
#include "Domain.h"
#include "Exceptions.h"
#include <string>
#include <vector>
#include <memory>

class Service: public Subject
{
private:
	Repository<Star>& entities;

public:
	Service(Repository<Star>& entitiesNew) : entities{ entitiesNew }{};
	~Service() {};

	std::vector<Star> getAll();
	void addStar(std::string name, std::string constellation, int RA, int Dec, int diameter);
	std::vector<Star> getFiltered(std::string filter);

};