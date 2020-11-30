#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Star
{
private:
	std::string name;
	std::string constellation;
	int RA;
	int Dec;
	int diameter;

public:
	Star() : name{ "" }, constellation{ "" }, RA{ 0 }, Dec{ 0 }, diameter{ 0 } {};
	Star(const std::string& name, const std::string& constellation, const int RA, const int Dec, const int diameter) :
		name{ name }, constellation{ constellation }, RA{ RA }, Dec{ Dec }, diameter{ diameter }{};
	Star(const Star& entity);
	bool operator==(const Star& otherEntity) const;
	~Star() {};

	std::string getName() const { return name; }
	std::string getConstellation() const { return constellation; }
	int getRA() const { return RA; }
	int getDec() const { return Dec; }
	int getDiameter() const { return diameter; }


	static std::vector<std::string> splitString(const std::string& tapeLine);

	friend std::istream& operator>>(std::istream& istream, Star& entity);
	friend std::ostream& operator<<(std::ostream& ostream, const Star& entity);
};

class Astronomer
{
private:
	std::string name;
	std::string constellation;

public:
	Astronomer() : name{ "" }, constellation{ "" } {};
	Astronomer(const std::string& name, const std::string& coordinator) :
		name{ name }, constellation{ coordinator }{};
	Astronomer(const Astronomer& entity);
	bool operator==(const Astronomer& otherEntity) const;
	~Astronomer() {};

	std::string getName() const { return name; }
	std::string getConstellation() const { return constellation; }

	static std::vector<std::string> splitString(const std::string& tapeLine);

	friend std::istream& operator>>(std::istream& istream, Astronomer& entity);
	friend std::ostream& operator<<(std::ostream& ostream, const Astronomer& entity);

};


