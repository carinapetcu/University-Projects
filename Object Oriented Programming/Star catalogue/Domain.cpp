#include "Domain.h"

std::istream& operator>>(std::istream& istream, Star& entity)
{
	std::string tapeLine;
	std::getline(istream, tapeLine);
	std::vector<std::string> lineParts;
	if (tapeLine == "")
	{
		return istream;
	}
	lineParts = Star::splitString(tapeLine);
	entity.name = lineParts[0];
	entity.constellation = lineParts[1];
	entity.RA = std::stoi(lineParts[2]);
	entity.Dec = std::stoi(lineParts[3]);
	entity.diameter = std::stoi(lineParts[4]);
	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Star& entity)
{
	std::string result;
	result.append(entity.getName());
	result.append(",");
	result.append(entity.getConstellation());
	result.append(",");
	result.append(std::to_string(entity.getRA()));
	result.append(",");
	result.append(std::to_string(entity.getDec()));
	result.append(",");
	result.append(std::to_string(entity.getDiameter()));
	result.append("\n");
	ostream << result;
	return ostream;
}

std::istream& operator>>(std::istream& istream, Astronomer& entity)
{
	std::string tapeLine;
	std::getline(istream, tapeLine);
	std::vector<std::string> lineParts;
	if (tapeLine == "")
	{
		return istream;
	}
	lineParts = Astronomer::splitString(tapeLine);
	entity.name = lineParts[0];
	entity.constellation = lineParts[1];
	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Astronomer& entity)
{
	std::string result;
	result.append(entity.getName());
	result.append(",");
	result.append(entity.getConstellation());
	result.append("\n");
	ostream << result;
	return ostream;
}

Astronomer::Astronomer(const Astronomer& entity)
{
	this->name = entity.name;
	this->constellation = entity.constellation;
}

bool Astronomer::operator==(const Astronomer& otherEntity) const
{
	return (this->name == otherEntity.name);
}

std::vector<std::string> Astronomer::splitString(const std::string& tapeLine)
{
	std::vector <std::string> result;
	std::stringstream ss(tapeLine);
	std::string token;
	const char delimitate = ',';
	while (std::getline(ss, token, delimitate))
	{
		result.push_back(token);
	}
	return result;
}

Star::Star(const Star& entity)
{
	this->name = entity.name;
	this->constellation = entity.constellation;
	this->RA = entity.RA;
	this->Dec = entity.Dec;
	this->diameter = entity.diameter;
}

bool Star::operator==(const Star& otherEntity) const
{
	return (this->name == otherEntity.name);
}

std::vector<std::string> Star::splitString(const std::string& tapeLine)
{
	std::vector <std::string> result;
	std::stringstream ss(tapeLine);
	std::string token;
	const char delimitate = ',';
	while (std::getline(ss, token, delimitate))
	{
		result.push_back(token);
	}
	return result;
}
