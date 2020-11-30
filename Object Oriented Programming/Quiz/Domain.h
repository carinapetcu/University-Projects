#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Participant
{
private:
	std::string name;
	int score;

public:
	Participant() : name{ "" }, score{ 0 } {};
	Participant(const std::string& name, const int& score) : name{ name }, score{ score } {};
	Participant(const Participant& entity);
	bool operator==(const Participant& otherEntity) const;
	~Participant() {};

	std::string getName() const { return name; };
	int getScore() const { return score; };

	static std::vector<std::string> splitString(const std::string& tapeLine);

	friend std::istream& operator>>(std::istream& istream, Participant& entity);
	friend std::ostream& operator<<(std::ostream& ostream, const Participant& entity);

	void setName(std::string newName) { name = newName; };
	void setScore(int newScore) { score = newScore; };
};

class Question
{
private:
	int id;
	std::string text;
	std::string correctAnswer;
	int score;

public:
	Question() : id{ 0 }, text{ "" }, correctAnswer{ "" }, score{ 0 } {};
	Question(const int& id, const std::string& text, const std::string& correctAnswer, const int& score) : id{ id }, text{ text }, correctAnswer{correctAnswer}, score{ score } {};
	Question(const Question& entity);
	bool operator==(const Question& otherEntity) const;
	~Question() {};

	std::string getText() const { return text; };
	int getScore() const { return score; };
	std::string getCorrectAnswer() const { return correctAnswer; };
	int getId() const { return id; };

	static std::vector<std::string> splitString(const std::string& tapeLine);

	friend std::istream& operator>>(std::istream& istream, Question& entity);
	friend std::ostream& operator<<(std::ostream& ostream, const Question& entity);

	void setText(std::string newText) { text = newText; };
	void setCorrectAnswer(std::string newCorrectAnswer) { correctAnswer = newCorrectAnswer; };
	void setScore(int newScore) { score = newScore; };
};



