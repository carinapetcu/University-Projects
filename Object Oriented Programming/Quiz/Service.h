#pragma once
#include "Repository.h"
#include "Observer.h"
#include "Domain.h"
#include <string>
#include <vector>
#include <memory>
#include <map>

class Service: public Subject
{
private:
	Repository<Question>& questions;
	Repository<Participant>& participants;
	std::multimap<std::string, int> answeredQuestion{};

public:
	Service(Repository<Question>& questionsNew, Repository<Participant>& participantsNew) : questions{ questionsNew }, participants{ participantsNew } {};
	~Service() {};
	
	std::vector<Question> getAllQuestions();
	std::vector<Question> getAllSortedByScore();
	void addQuestion(int id, std::string text, std::string correctAnswer, int score);
	Participant updateParticipant(std::string name, int score);

	void addAnswered(std::string name, int idOfQuestion);
	bool isAnswered(std::string name, int idOfQuestion);

};