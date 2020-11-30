#include "Service.h"
#include <iostream>
#include <vector>
#include <QtCore\qlogging.h>

std::vector<Student> Service::getAllStudentCoordinatedByTeacher(std::string teacherName)
{
	std::vector<Student> studentsCoordinatedByTeacher;
	std::vector<Student> allStudents = this->students.getAll();

	for (auto student : allStudents)
		if (student.getCoordinator() == teacherName)
			studentsCoordinatedByTeacher.push_back(student);

	std::sort(studentsCoordinatedByTeacher.begin(), studentsCoordinatedByTeacher.end(), [](Student first, Student second) {return first.getYear() > second.getYear(); });
	return studentsCoordinatedByTeacher;
}

std::vector<Student> Service::filterStudentsByNameOrId(std::string filter)
{
	std::vector<Student> filteredStudents;
	std::vector<Student> allStudents = this->students.getAll();
	
	for (auto& student : allStudents)
	{
		std::string name = student.getName();
		std::string id = student.getId();
		auto iterator1 = std::search(
			name.begin(), name.end(),
			filter.begin(), filter.end(),
			[](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
		);
		auto iterator2 = std::search(
			id.begin(), id.end(),
			filter.begin(), filter.end(),
			[](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
		);
		if (iterator1 != name.end() || iterator2 != id.end())
			filteredStudents.push_back(student);
	}
	return filteredStudents;
}

void Service::addTeacherAsCoordinator(std::string studentId, std::string teacherName)
{
	std::vector<Student> allStudents = this->students.getAll();
	for (auto student : allStudents)
	{
		if (student.getId() == studentId)
		{
			student.setCoordinator(teacherName);
			this->students.update(student);
			this->notify();
		}
	}
}

void Service::updateEmail(std::string studentId, std::string email)
{
	std::vector<Student> allStudents = this->students.getAll();
	for (auto student : allStudents)
	{
		if (student.getId() == studentId)
		{
			student.setEmail(email);
			this->students.update(student);
			this->notify();
		}
	}
}

void Service::updateThesisTitle(std::string studentId, std::string title)
{
	std::vector<Student> allStudents = this->students.getAll();
	for (auto student : allStudents)
	{
		if (student.getId() == studentId)
		{
			student.setTitle(title);
			this->students.update(student);
			this->notify();
		}
	}
}
