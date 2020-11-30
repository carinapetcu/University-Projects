#pragma once
#include "Repository.h"
#include "Domain.h"
#include <string>
#include <vector>

class Service 
{
private:
	Repository<Domain>& repository;

public:
	Service(Repository<Domain>& repositoryNew) : repository{ repositoryNew } {};
	~Service() {};

	std::vector<Domain> getAllElements();

};