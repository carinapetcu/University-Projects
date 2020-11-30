#include "Tape.h"
#include <string>

Date::~Date(){}

Tape::Tape(): title(""), section(""), date(Date()), accessCount(0), footagePreview("") {}

bool Tape::operator==(const Tape& otherTape) const
{
	return title == otherTape.title;
}

Tape::Tape(const std::string& title, const std::string& section, const Date& date, const int& accessCount, const std::string& footagePreview)
{
	this->title = title;
	this->section = section;
	this->date = date;
	this->accessCount = accessCount;
	this->footagePreview = footagePreview;
}

Tape::Tape(const Tape& tape)
{
	this->title = tape.title;
	this->section = tape.section;
	this->date = tape.date;
	this->accessCount = tape.accessCount;
	this->footagePreview = tape.footagePreview;
}

Tape::~Tape(){}

std::vector<std::string> Tape::splitString(const std::string& tapeLine)
{
	std::vector <std::string> result;
	std::stringstream ss(tapeLine);
	std::string token;
	const char delimitate = ',';
	while (std::getline(ss, token, delimitate))
		result.push_back(token);

	return result;

}

std::istream& operator>>(std::istream& istream, Tape& tape)
{
	std::string tapeLine;
	std::getline(istream, tapeLine);
	std::vector<std::string> lineParts;
	if (tapeLine == "")
	{
		return istream;
	}

	lineParts = Tape::splitString(tapeLine);
	tape.title = lineParts[0];
	tape.section = lineParts[1];
	tape.accessCount = std::stoi(lineParts[3]);
	tape.footagePreview = lineParts[4];
	
	std::size_t positionOfMinus = lineParts[2].find("-");
	int month = stoi(lineParts[2].substr(0, positionOfMinus));
	lineParts[2].erase(0, positionOfMinus + 1);
	positionOfMinus = lineParts[2].find("-");
	int day = stoi(lineParts[2].substr(0, positionOfMinus));
	lineParts[2].erase(0, positionOfMinus + 1);
	int year = stoi(lineParts[2].substr(0));
	tape.date = Date{ month, day, year };

	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Tape& tape)
{
	std::string result;
	result.append(tape.getTitle());
	result.append(",");
	result.append(tape.getSection());
	result.append(",");
	result.append(std::to_string(tape.getDate().getMonth()));
	result.append("-");
	result.append(std::to_string(tape.getDate().getDay()));
	result.append("-");
	result.append(std::to_string(tape.getDate().getYear()));
	result.append(",");
	result.append(std::to_string(tape.getAccessCount()));
	result.append(",");
	result.append(tape.getFootagePreview());
	result.append("\n");
	ostream << result;
	return ostream;

}