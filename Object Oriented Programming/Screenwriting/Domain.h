#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Writer
{
private:
	std::string name;
	std::string expertise;

public:
	Writer() :name{ "" }, expertise{ "" } {};
	Writer(const std::string& name, const std::string& expertise) : name{ name }, expertise{ expertise }{};
	Writer(const Writer& entity);
	bool operator==(const Writer& otherEntity) const;
	~Writer() {};

	std::string getName() const { return name; }
	std::string getExpertise() const { return expertise; }

	static std::vector<std::string> splitString(const std::string& tapeLine);

	friend std::istream& operator>>(std::istream& istream, Writer& entity);
	friend std::ostream& operator<<(std::ostream& ostream, const Writer& entity);
};

class Idea
{
private:
	std::string description;
	std::string status;
	std::string creator;
	int act;

public:
	Idea() : description{ "" }, status{ "" }, creator{ "" }, act{ 0 } {};
	Idea(const std::string& description, const std::string& status, const std::string& creator, const int act) : description{ description }, status{ status }, creator{ creator }, act{ act }{};
	Idea(const Idea& entity);
	bool operator==(const Idea& otherEntity) const;
	~Idea() {};

	std::string getDescription() const { return description; }
	std::string getStatus() const { return status; }
	std::string getCreator() const { return creator; }
	int getAct() const { return act; }

	static std::vector<std::string> splitString(const std::string& tapeLine);

	friend std::istream& operator>>(std::istream& istream, Idea& entity);
	friend std::ostream& operator<<(std::ostream& ostream, const Idea& entity);

	void setStatus(std::string newStatus) { status = newStatus; }
};

