#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class User
{
private:
	std::string name;
	std::string type;

public:
	User() : name{ "" }, type{ "" } {};
	User(const std::string& name, const std::string& type): name{ name }, type{type} {};
	User(const User& entity);
	bool operator==(const User& otherEntity) const;
	~User() {};

	std::string getName() const { return name; }
	std::string getType() const { return type; }

	static std::vector<std::string> splitString(const std::string& tapeLine);

	friend std::istream& operator>>(std::istream& istream, User& entity);
	friend std::ostream& operator<<(std::ostream& ostream, const User& entity);

	void setName(std::string newName) { name = newName; }
	void setType(std::string newType) { type = newType; }
};

class Issue
{
private:
	std::string description;
	std::string status;
	std::string reporter;
	std::string solver;

public:
	Issue() : description{ "" }, status{ "" }, reporter{ "" }, solver{""} {};
	Issue(const std::string& description, const std::string& status, const std::string& reporter, const std::string& solver) : description{ description }, 
		status{ status }, reporter{ reporter }, solver{solver} {};
	Issue(const Issue& entity);
	bool operator==(const Issue& otherEntity) const;
	~Issue() {};

	std::string getDescription() const { return description; }
	std::string getStatus() const { return status; }
	std::string getReporter() const { return reporter; }
	std::string getSolver() const { return solver; }

	static std::vector<std::string> splitString(const std::string& tapeLine);

	friend std::istream& operator>>(std::istream& istream, Issue& entity);
	friend std::ostream& operator<<(std::ostream& ostream, const Issue& entity);

	
	void setDescription(std::string newDescription) { description = newDescription; }
	void setStatus(std::string newStatus) { status = newStatus; }
	void setReporter(std::string newReporter) { reporter = newReporter; }
	void setSolver(std::string newSolver) { solver = newSolver; }
};



