#include "Service.h"
#include <iostream>
#include <vector>
#include <QtCore\qlogging.h>

std::vector<Star> Service::getAll()
{
	std::vector<Star> allStars = this->entities.getAll();
	return allStars;
}

/*
input: name, which is the name of the star, constellation, which is the constellation which the star belongs to, RA, which is the right ascension of the star, 
		Dec, which is the declination of the star and diameter which is the diameter of the star
the function creates a new Star entity and adds it to the repository, as well as notifying the Observer that the service has been changed
*/
void Service::addStar(std::string name, std::string constellation, int RA, int Dec, int diameter)
{
	Star star{ name, constellation, RA, Dec, diameter };
	this->entities.add(star);
	this->notify();
}

std::vector<Star> Service::getFiltered(std::string filter)
{
	std::vector<Star> filteredStars;
	std::vector<Star> allStars = this->entities.getAll();

	for (auto& star : allStars)
	{
		std::string name = star.getName();
		auto iterator1 = std::search(
			name.begin(), name.end(),
			filter.begin(), filter.end(),
			[](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
		);
		if (iterator1 != name.end())
			filteredStars.push_back(star);
	}
	return filteredStars;
}
