#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

class Date
{
private:
	int month;
	int day;
	int year;

public:
	Date() : month(0), day(0), year(0) { }
	Date(int newMonth, int newDay, int newYear): month(newMonth), day(newDay), year(newYear) {}
	~Date();

	int getMonth() const { return month; }
	int getDay() const { return day; }
	int getYear() const { return year; }

	void setMonth(int newMonth) { month = newMonth; }
	void setDay(int newDay) { day = newDay; }
	void setYear(int newYear) { year = newYear; }
};

class Tape
{
private:
	std::string title;
	std::string section;
	Date date;
	int accessCount;
	std::string footagePreview;

public:
	Tape();
	Tape(const std::string& title, const std::string& section, const Date& date, const int& accessCount, const std::string& footagePreview);
	Tape(const Tape& tape);
	bool operator==(const Tape& otherTape) const;
	~Tape();

	std::string getTitle() const { return title; }
	std::string getSection() const { return section; }
	Date getDate() const { return date; }
	int getAccessCount() const { return accessCount; }
	std::string getFootagePreview() const { return footagePreview; }

	static std::vector<std::string> splitString(const std::string& tapeLine);

	friend std::istream& operator>>(std::istream& istream, Tape& tape);
	friend std::ostream& operator<<(std::ostream& ostream, const Tape& tape);

	void setTitle(std::string newTitle) { title = newTitle; }
	void setSection(std::string newSection) { section = newSection; }
	void setDate(Date newDate) { date = newDate; }
	void setAccessCount(int newAccessCount) { accessCount = newAccessCount; }
	void setFootagePreview(std::string newFootagePreview) { footagePreview = newFootagePreview; }
};