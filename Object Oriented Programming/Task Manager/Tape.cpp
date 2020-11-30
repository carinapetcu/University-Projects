#include "Tape.h"
#include <string>

Task::Task(): description(""), duration(0), priority(0) {}

bool Task::operator==(const Task& otherTape) const
{
	return description == otherTape.description;
}

Task::Task(const std::string& description, const int& duration, const int& priority)
{
	this->description = description;
	this->duration = duration;
	this->priority = priority;
}

Task::Task(const Task& tape)
{
	this->description = tape.description;
	this->duration = tape.duration;
	this->priority = tape.priority;
}

Task::~Task(){}

std::vector<std::string> Task::splitString(const std::string& tapeLine)
{
	std::vector <std::string> result;
	std::stringstream ss(tapeLine);
	std::string token;
	const char delimitate = '|';
	while (std::getline(ss, token, delimitate))
		result.push_back(token);

	return result;

}

std::istream& operator>>(std::istream& istream, Task& tape)
{
	std::string tapeLine;
	std::getline(istream, tapeLine);
	std::vector<std::string> lineParts;
	if (tapeLine == "")
	{
		return istream;
	}

	lineParts = Task::splitString(tapeLine);
	tape.description = lineParts[0];
	tape.duration = std::stoi(lineParts[1]);
	tape.priority = std::stoi(lineParts[2]);
	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Task& tape)
{
	std::string result;
	result.append(tape.getDescription());
	result.append("|");
	result.append(std::to_string(tape.getDuration()));
	result.append("|");
	result.append(std::to_string(tape.getPriority()));
	result.append("\n");
	ostream << result;
	return ostream;

}