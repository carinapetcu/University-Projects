#include "Service.h"
#include <iostream>

void Service::addQuestion(const std::string& text, const std::string& name)
{
	int id = rand() % 1000;
	std::vector<Question> questions = this->questions.getAll();
	while (std::find(questions.begin(), questions.end(), Question{ id, "", "" }) != questions.end())
		id = rand() % 1000;
	Question question{ id, text, name };
	this->questions.add(question);
	this->notify();
}

std::vector<Question> Service::getAllQuestions()
{
	std::vector<Question> questions = this->questions.getAll();
	std::vector<Answer> answers = this->answers.getAll();
	int howManyAnswers[200] = { 0 };
	for (auto answer : answers)
		howManyAnswers[answer.getQuestionId()]++;
	for(int index1 = 0 ; index1 < questions.size()-1; index1++)
		for(int index2 = index1+1; index2 < questions.size(); index2++)
			if (howManyAnswers[questions[index1].getId()] < howManyAnswers[questions[index2].getId()]) {
				std::swap(questions[index1], questions[index2]);
			}
	return questions;
}

void Service::addAnswer(int questionId, const std::string& name, const std::string& answer, const int votes)
{
	int id = rand() % 1000;
	std::vector<Answer> answers = this->answers.getAll();
	while (std::find(answers.begin(), answers.end(), Answer{id, questionId, name, answer, votes}) != answers.end())
		id = rand() % 1000;
	Answer newAnswer{ id, questionId, name, answer, votes };
	this->answers.add(newAnswer);
	this->notify();
}

std::vector<std::string> Service::getAllAnswers(std::string filter)
{
	std::vector<Question> questions = this->questions.getAll();
	std::vector<Answer> answers = this->answers.getAll();
	int maximumMatchingLetters = -1;
	int currentMatchingLetters;
	int questionId{};
	std::string maximumMatchingLettersQuestion;
	for (auto question : questions)
	{
		currentMatchingLetters = 0;
		std::string currentQuestion = question.getText();
		for (int index = 0; index < filter.size(); index++)
			if (currentQuestion[index] == filter[index])
				currentMatchingLetters++;
		if (currentMatchingLetters > maximumMatchingLetters)
		{
			questionId = question.getId();
			maximumMatchingLettersQuestion = currentQuestion;
			maximumMatchingLetters = currentMatchingLetters;
		}
	}
	int first = -1, second = -1, third = -1;
	std::string firstAnswer, secondAnswer, thirdAnswer;
	for (auto answer : answers)
	{
		if (answer.getQuestionId() == questionId) {
			if (answer.getVotes() > first) {
				third = second;
				second = first;
				first = answer.getVotes();
				thirdAnswer = secondAnswer;
				secondAnswer = firstAnswer;
				firstAnswer = answer.getText();
			}
			else if (answer.getVotes() > second) {
				third = second;
				second = answer.getVotes();
				thirdAnswer = secondAnswer;
				secondAnswer = answer.getText();
			} 
			else if (answer.getVotes() > third) {
				third = answer.getVotes();
				thirdAnswer = answer.getText();
			}
		}
	}
	std::vector<std::string> list;
	list.push_back(maximumMatchingLettersQuestion);
	if(first != -1)
		list.push_back(firstAnswer);
	if(second != -1)
		list.push_back(secondAnswer);
	if (third != -1)
		list.push_back(thirdAnswer);
	return list;
}

std::vector<Answer> Service::getAnswers(int questionId)
{
	std::vector<Answer> answers = this->answers.getAll();
	std::vector<Answer> allAnswers;
	for (auto answer : answers)
		if (answer.getQuestionId() == questionId)
			allAnswers.push_back(answer);
	return allAnswers;
}
