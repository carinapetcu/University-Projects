#include "Service.h"
#include <iostream>

std::vector<Task> Service::getAllElements()
{
	return this->repository.getAll();
	
}