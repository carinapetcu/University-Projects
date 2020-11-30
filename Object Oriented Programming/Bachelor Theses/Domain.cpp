#include "Domain.h"

Student::Student(const Student& entity)
{
	this->id = entity.id;
	this->name = entity.name;
	this->email = entity.email;
	this->year = entity.year;
	this->title = entity.title;
	this->coordinator = entity.coordinator;
}

bool Student::operator==(const Student& otherEntity) const
{
	return this->name == otherEntity.name;
}

std::vector<std::string> Student::splitString(const std::string& tapeLine)
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

std::istream& operator>>(std::istream& istream, Student& entity)
{
	std::string tapeLine;
	std::getline(istream, tapeLine);
	std::vector<std::string> lineParts;
	if (tapeLine == "")
	{
		return istream;
	}
	lineParts = Student::splitString(tapeLine);
	entity.id = lineParts[0];
	entity.name = lineParts[1];
	entity.email = lineParts[2];
	entity.year = std::stoi(lineParts[3]);
	entity.title = lineParts[4];
	entity.coordinator = lineParts[5];
	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Student& entity)
{
	std::string result;
	result.append(entity.getId());
	result.append(",");
	result.append(entity.getName());
	result.append(",");
	result.append(entity.getEmail());
	result.append(",");
	result.append(std::to_string(entity.getYear()));
	result.append(",");
	result.append(entity.getTitle());
	result.append(",");
	result.append(entity.getCoordinator());
	result.append("\n");
	ostream << result;
	return ostream;
}
