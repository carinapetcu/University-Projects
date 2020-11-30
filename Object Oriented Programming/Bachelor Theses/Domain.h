#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Student
{
private:
	std::string id;
	std::string name;
	std::string email;
	int year;
	std::string title;
	std::string coordinator;

public:
	Student() : id{ "" }, name{ "" }, email{ "" }, year{ 0 }, title{ "" }, coordinator{ "" } {};
	Student(const std::string& id, const std::string& name, const std::string& email, const int year, const std::string& title, const std::string& coordinator) : 
		id{ id }, name{ name }, email{ email }, year{ year }, title{title}, coordinator{ coordinator }{};
	Student(const Student& entity);
	bool operator==(const Student& otherEntity) const;
	~Student() {};

	std::string getId() const { return id; }
	std::string getName() const { return name; }
	std::string getEmail() const { return email; }
	int getYear() const { return year; }
	std::string getTitle() const { return title; }
	std::string getCoordinator() const { return coordinator; }

	static std::vector<std::string> splitString(const std::string& tapeLine);

	friend std::istream& operator>>(std::istream& istream, Student& entity);
	friend std::ostream& operator<<(std::ostream& ostream, const Student& entity);

	void setEmail(std::string newEmail) { email = newEmail; }
	void setTitle(std::string newTitle) { title = newTitle; }
	void setCoordinator(std::string newCoordinator) { coordinator = newCoordinator; }

};

