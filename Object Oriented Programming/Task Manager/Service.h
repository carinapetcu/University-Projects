#pragma once
#include "Repository.h"
#include "Tape.h"
#include <string>
#include <vector>

class Service 
{
private:
	Repository& repository;

public:
	Service(Repository& repositoryNew) : repository{ repositoryNew } {};
	~Service() {};

	std::vector<TElement> getAllElements();

};