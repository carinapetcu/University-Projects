#include "Domain.h"

Domain::Domain(const std::string& companyName, const std::string& code, const float sum, const bool isPaid)
{
	this->companyName = companyName;
	this->code = code;
	this->sum = sum;
	this->isPaid = isPaid;
}

Domain::Domain(const Domain& entity)
{
	this->companyName = entity.companyName;
	this->code = entity.code;
	this->sum = entity.sum;
	this->isPaid = entity.isPaid;
}

bool Domain::operator==(const Domain& otherEntity) const
{
	return (this->code == otherEntity.code);
}

std::vector<std::string> Domain::splitString(const std::string& tapeLine)
{
	std::vector <std::string> result;
	std::stringstream ss(tapeLine);
	std::string token;
	const char delimitate = ';';
	while(std::getline(ss, token, delimitate))
	{
		result.push_back(token);
	}
	return result;
}

std::istream& operator>>(std::istream& istream, Domain& entity)
{
	std::string tapeLine;
	std::getline(istream, tapeLine);
	std::vector<std::string> lineParts;
	if (tapeLine == "")
	{
		return istream;
	}

	lineParts = Domain::splitString(tapeLine);
	entity.companyName = lineParts[0];
	entity.code = lineParts[1];
	entity.sum = std::stof(lineParts[2]);
	if (lineParts[3] == "true")
		entity.isPaid = true;
	else
		entity.isPaid = false;
	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Domain& entity)
{
	std::string result;
	result.append(entity.getCompanyName());
	result.append(";");
	result.append(entity.getCode());
	result.append(";");
	result.append(std::to_string(entity.getSum()));
	result.append(";");
	if (entity.isPaid)
		result.append("true");
	else
		result.append("false");
	ostream << result;
	return ostream;
}
