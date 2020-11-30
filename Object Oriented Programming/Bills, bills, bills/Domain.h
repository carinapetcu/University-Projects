#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Domain
{
private:
	std::string companyName;
	std::string code;
	float sum;
	bool isPaid;

public:
	Domain() : companyName{ "" }, code{ "" }, sum{ 0 }, isPaid{false} {};
	Domain(const std::string& companyName, const std::string& code, const float sum, const bool isPaid);
	Domain(const Domain& entity);
	bool operator==(const Domain& otherEntity) const;
	~Domain() {};

	std::string getCompanyName() const { return companyName; }
	std::string getCode() const { return code; }
	float getSum() const { return sum; }
	bool getIsPaid() const { return isPaid; }

	static std::vector<std::string> splitString(const std::string& tapeLine);

	friend std::istream& operator>>(std::istream& istream, Domain& entity);
	friend std::ostream& operator<<(std::ostream& ostream, const Domain& entity);

	void setCompanyName(std::string newCompanyName) { companyName = newCompanyName; }
	void setCode(std::string newCode) { code = newCode; }
	void setSum(float newSum) {  sum = newSum; }
	void setIsPaid(bool newIsPaid) {isPaid = newIsPaid; }
};

