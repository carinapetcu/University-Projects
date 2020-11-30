#include "Domain.h"

Domain::Domain(const std::string& family, const std::string& name, const std::vector<std::string>& consumed)
{
	this->family = family;
	this->name = name;
	this->consumed.clear();
	this->consumed = consumed;
}

Domain::Domain(const Domain& entity)
{
	this->family = entity.family;
	this->name = entity.name;
	this->consumed.clear();
	this->consumed = entity.consumed;
}

bool Domain::operator==(const Domain& otherEntity) const
{
	return (this->name == otherEntity.name);
}

std::vector<std::string> Domain::splitString(const std::string& tapeLine)
{
	std::vector <std::string> result;
	std::stringstream ss(tapeLine);
	std::string token;
	const char delimitate = '|';
	for (int i = 0; i < 2; i++)
	{
		std::getline(ss, token, delimitate);
		result.push_back(token);
	}
	std::getline(ss, token, delimitate);
	std::stringstream ss1(token);
	const char delimitate1 = ',';
	while (std::getline(ss1, token, delimitate1))
		result.push_back(token);
	return result;
}

std::istream& operator>>(std::istream& istream, Domain& entity)
{
	std::string tapeLine;
	std::getline(istream, tapeLine);
	std::vector<std::string> lineParts;
	if (tapeLine == "")
	{
		return istream;
	}

	lineParts = Domain::splitString(tapeLine);
	entity.family = lineParts[0];
	entity.name = lineParts[1];
	entity.consumed.clear();
	for (int index = 2; index < lineParts.size(); index++)
	{
		entity.consumed.push_back(lineParts[index]);
	}
	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Domain& entity)
{
	std::string result;
	result.append(entity.getFamily());
	result.append("|");
	result.append(entity.getName());
	result.append("|");
	result.append(entity.consumed[0]);
	for (int index = 1; index < entity.consumed.size(); index++)
	{
		result.append(",");
		result.append(entity.consumed[index]);
	}
	ostream << result;
	return ostream;
}
