#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Question
{
private:
	int id;
	std::string text;
	std::string name;

public:
	Question() : id{ 0 }, text{ "" }, name{ "" } {};
	Question(int id, const std::string& text, const std::string& name);
	Question(const Question& entity);
	bool operator==(const Question& otherEntity) const;
	~Question() {};

	int getId() const { return id; }
	std::string getName() const { return name; }
	std::string getText() const { return text; }

	static std::vector<std::string> splitString(const std::string& tapeLine);

	friend std::istream& operator>>(std::istream& istream, Question& entity);
	friend std::ostream& operator<<(std::ostream& ostream, const Question& entity);

	void setName(std::string newName) { name = newName; }
	void setText(std::string newText) { text = newText; }
};

class Answer
{
private:
	int id;
	int questionId;
	std::string name;
	std::string text;
	int votes;

public:
	Answer() : id{ 0 }, questionId{ 0 }, name{ "" }, text{ "" }, votes{ 0 } {};
	Answer(int id, const int questionId, const std::string& name, const std::string& text, const int votes);
	Answer(const Answer& entity);
	bool operator==(const Answer& otherEntity) const;
	~Answer() {};

	int getId() const { return id; }
	int getQuestionId() const { return questionId; }
	std::string getName() const { return name; }
	std::string getText() const { return text; }
	int getVotes() const { return votes; }

	static std::vector<std::string> splitString(const std::string& tapeLine);

	friend std::istream& operator>>(std::istream& istream, Answer& entity);
	friend std::ostream& operator<<(std::ostream& ostream, const Answer& entity);

	void setQuestionId(int newQuestionId) { questionId = newQuestionId; }
	void setName(std::string newName) { name = newName; }
	void setText(std::string newText) { text = newText; }
	void setVotes(int newVotes) { votes = newVotes; }
};

