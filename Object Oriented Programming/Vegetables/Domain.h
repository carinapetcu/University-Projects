#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Domain
{
private:
	std::string family;
	std::string name;
	std::vector<std::string> consumed;
public:
	Domain() : family{ "" }, name{ "" }, consumed{} {};
	Domain(const std::string& family, const std::string& name, const std::vector<std::string>& consumed);
	Domain(const Domain& entity);
	bool operator==(const Domain& otherEntity) const;
	~Domain() {};

	std::string getFamily() const { return family; }
	std::string getName() const { return name; }
	std::vector<std::string> getConsumed() const { return consumed; }

	static std::vector<std::string> splitString(const std::string& tapeLine);

	friend std::istream& operator>>(std::istream& istream, Domain& entity);
	friend std::ostream& operator<<(std::ostream& ostream, const Domain& entity);

	void setFamily(std::string newFamily) { family = newFamily; }
	void setName(std::string newName) { name = newName; }
	void setConsumed(std::vector<std::string> newConsumed) { consumed = newConsumed; }
};

