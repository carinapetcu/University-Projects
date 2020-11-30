#include "Service.h"
#include "Exceptions.h"
#include <iostream>

std::vector<Question> Service::getAllQuestions()
{
	return this->questions.getAll();
}

std::vector<Question> Service::getAllSortedByScore()
{
	std::vector<Question> allQuestions = this->questions.getAll();
	for (int index1 = 0; index1 < allQuestions.size() - 1; index1++)
		for (int index2 = index1; index2 < allQuestions.size(); index2++)
			if (allQuestions[index1].getScore() < allQuestions[index2].getScore())
				std::swap(allQuestions[index1], allQuestions[index2]);
	return allQuestions;
}

void Service::addQuestion(int id, std::string text, std::string correctAnswer, int score)
{
	score = rand() % 100;
	Question newQuestion{ id, text, correctAnswer, score };
	this->questions.add(newQuestion);
	this->notify();
}

Participant Service::updateParticipant(std::string name, int score)
{
	Participant participant{ name, score };
	this->participants.update(participant);
	this->notify();
	return participant;
}

void Service::addAnswered(std::string name, int idOfQuestion)
{
	this->answeredQuestion.insert(std::pair<std::string, int>(name, idOfQuestion));
	this->notify();
}

bool Service::isAnswered(std::string name, int idOfQuestion)
{
	for (auto element : this->answeredQuestion)
		if (element.first == name && element.second == idOfQuestion)
			return true;
	return false;
}
