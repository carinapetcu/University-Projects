#pragma once
#include "Repository.h"
#include "Observer.h"
#include "Domain.h"
#include "Exceptions.h"
#include <string>
#include <vector>
#include <memory>
//#include "Observer.h"

class Service: public Subject
{
private:
	Repository<Student>& students;

public:
	Service(Repository<Student>& studentsNew) : students{ studentsNew }{};
	~Service() {};

	std::vector<Student> getAll() { return this->students.getAll(); };
	std::vector<Student> getAllStudentCoordinatedByTeacher(std::string teacherName);
	std::vector<Student> filterStudentsByNameOrId(std::string filter);

	void addTeacherAsCoordinator(std::string studentId, std::string teacherName);
	void updateEmail(std::string studentId, std::string email);
	void updateThesisTitle(std::string studentId, std::string title);

};