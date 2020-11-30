#include "Service.h"
#include <iostream>

std::vector<Domain> Service::getAllElements()
{
	return this->repository.getAll();
	
}