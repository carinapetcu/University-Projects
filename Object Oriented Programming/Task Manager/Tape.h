#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

class Task
{
private:
	std::string description;
	int duration;
	int priority;

public:
	Task();
	Task(const std::string& description, const int& duration, const int& priority);
	Task(const Task& tape);
	bool operator==(const Task& otherTape) const;
	~Task();

	std::string getDescription() const { return description; }
	int getDuration() const { return duration; }
	int getPriority() const { return priority; }

	static std::vector<std::string> splitString(const std::string& tapeLine);

	friend std::istream& operator>>(std::istream& istream, Task& tape);
	friend std::ostream& operator<<(std::ostream& ostream, const Task& tape);

	void setDescription(std::string newDescription) { description = newDescription; }
	void setDuration(int newDuration) { duration = newDuration; }
	void setPriority(int newPriority) { priority = newPriority; }
};