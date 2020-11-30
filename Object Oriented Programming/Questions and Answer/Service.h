#pragma once
#include "Repository.h"
#include "Observer.h"
#include "Domain.h"
#include <string>
#include <vector>
#include <memory>
//#include "Observer.h"

class Service: public Subject
{
private:
	Repository<Question>& questions;
	Repository<Answer>& answers;

public:
	Service(Repository<Question>& questionsNew, Repository<Answer>& answersNew) : questions{ questionsNew }, answers{ answersNew } {};
	~Service() {};

	void addQuestion(const std::string& text, const std::string& name);
	std::vector<Question> getAllQuestions();

	void addAnswer(int questionId, const std::string& name, const std::string& answer, const int votes);
	void updateAnswer(const Answer& newAnswer) { answers.update(newAnswer); };
	std::vector<std::string> getAllAnswers(std::string filter);
	std::vector<Answer> getAnswers(int questionId);

};