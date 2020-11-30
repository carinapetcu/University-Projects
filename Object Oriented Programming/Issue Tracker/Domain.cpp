#include "Domain.h"


std::istream& operator>>(std::istream& istream, User& entity)
{
	std::string tapeLine;
	std::getline(istream, tapeLine);
	std::vector<std::string> lineParts;
	if (tapeLine == "")
	{
		return istream;
	}
	lineParts = User::splitString(tapeLine);
	entity.name = lineParts[0];
	entity.type = lineParts[1];
	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const User& entity)
{
	std::string result;
	result.append(entity.getName());
	result.append(",");
	result.append(entity.getType());
	result.append("\n");
	ostream << result;
	return ostream;
}

std::istream& operator>>(std::istream& istream, Issue& entity)
{
	std::string tapeLine;
	std::getline(istream, tapeLine);
	std::vector<std::string> lineParts;
	if (tapeLine == "")
	{
		return istream;
	}
	lineParts = Issue::splitString(tapeLine);
	entity.description = lineParts[0];
	entity.status = lineParts[1];
	entity.reporter = lineParts[2];
	entity.solver = lineParts[3];
	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Issue& entity)
{
	std::string result;
	result.append(entity.getDescription());
	result.append(",");
	result.append(entity.getStatus());
	result.append(",");
	result.append(entity.getReporter());
	result.append(",");
	result.append(entity.getSolver());
	result.append("\n");
	ostream << result;
	return ostream;
}

User::User(const User& entity)
{
	this->name = entity.name;
	this->type = entity.type;
}

bool User::operator==(const User& otherEntity) const
{
	return (this->name == otherEntity.name);
}

std::vector<std::string> User::splitString(const std::string& tapeLine)
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

Issue::Issue(const Issue& entity)
{
	this->description = entity.description;
	this->status = entity.status;
	this->reporter = entity.reporter;
	this->solver = entity.solver;
}

bool Issue::operator==(const Issue& otherEntity) const
{
	return (this->description == otherEntity.description);
}

std::vector<std::string> Issue::splitString(const std::string& tapeLine)
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
