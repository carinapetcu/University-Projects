#include "Domain.h"

Writer::Writer(const Writer& entity)
{
	this->name = entity.name;
	this->expertise = entity.expertise;
}

bool Writer::operator==(const Writer& otherEntity) const
{
	return (this->name == otherEntity.name);
}


std::vector<std::string> Writer::splitString(const std::string& tapeLine)
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

std::istream& operator>>(std::istream& istream, Writer& entity)
{
	std::string tapeLine;
	std::getline(istream, tapeLine);
	std::vector<std::string> lineParts;
	if (tapeLine == "")
	{
		return istream;
	}
	lineParts = Writer::splitString(tapeLine);
	entity.name = lineParts[0];
	entity.expertise = lineParts[1];
	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Writer& entity)
{
	std::string result;
	result.append(entity.getName());
	result.append(",");
	result.append(entity.getExpertise());
	result.append("\n");
	ostream << result;
	return ostream;
}

std::istream& operator>>(std::istream& istream, Idea& entity)
{
	std::string tapeLine;
	std::getline(istream, tapeLine);
	std::vector<std::string> lineParts;
	if (tapeLine == "")
	{
		return istream;
	}
	lineParts = Idea::splitString(tapeLine);
	entity.description = lineParts[0];
	entity.status = lineParts[1];
	entity.creator = lineParts[2];
	entity.act = std::stoi(lineParts[3]);
	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Idea& entity)
{
	std::string result;
	result.append(entity.getDescription());
	result.append(",");
	result.append(entity.getStatus());
	result.append(",");
	result.append(entity.getCreator());
	result.append(",");
	result.append(std::to_string(entity.getAct()));
	result.append("\n");
	ostream << result;
	return ostream;
}

Idea::Idea(const Idea& entity)
{
	this->description = entity.description;
	this->status = entity.status;
	this->creator = entity.creator;
	this->act = entity.act;
}

bool Idea::operator==(const Idea& otherEntity) const
{
	return (this->description == otherEntity.description && this->act == otherEntity.act);
}

std::vector<std::string> Idea::splitString(const std::string& tapeLine)
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
