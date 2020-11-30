#include "Domain.h"

std::istream& operator>>(std::istream& istream, Question& entity)
{
	std::string tapeLine;
	std::getline(istream, tapeLine);
	std::vector<std::string> lineParts;
	if (tapeLine == "")
	{
		return istream;
	}
	lineParts = Question::splitString(tapeLine);
	entity.id = std::stoi(lineParts[0]);
	entity.text = lineParts[1];
	entity.name = lineParts[2];
	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Question& entity)
{
	std::string result;
	result.append(std::to_string(entity.getId()));
	result.append(",");
	result.append(entity.getText());
	result.append(",");
	result.append(entity.getName());
	result.append("\n");
	ostream << result;
	return ostream;
}

std::istream& operator>>(std::istream& istream, Answer& entity)
{
	std::string tapeLine;
	std::getline(istream, tapeLine);
	std::vector<std::string> lineParts;
	if (tapeLine == "")
	{
		return istream;
	}
	lineParts = Answer::splitString(tapeLine);
	entity.id = std::stoi(lineParts[0]);
	entity.questionId = std::stoi(lineParts[1]);
	entity.name = lineParts[2];
	entity.text = lineParts[3];
	entity.votes = std::stoi(lineParts[4]);
	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Answer& entity)
{
	std::string result;
	result.append(std::to_string(entity.getId()));
	result.append(",");
	result.append(std::to_string(entity.getQuestionId()));
	result.append(",");
	result.append(entity.getText());
	result.append(",");
	result.append(entity.getName());
	result.append(",");
	result.append(std::to_string(entity.getVotes()));
	result.append("\n");
	ostream << result;
	return ostream;
}

Question::Question(int id, const std::string& text, const std::string& name) : id{ id }, text{ text }, name{ name }
{
}

Question::Question(const Question& entity)
{
	this->id = entity.id;
	this->text = entity.text;
	this->name = entity.name;
}

bool Question::operator==(const Question& otherEntity) const
{
	return (this->id == otherEntity.id);
}

std::vector<std::string> Question::splitString(const std::string& tapeLine)
{
	std::vector <std::string> result;
	std::stringstream ss(tapeLine);
	std::string token;
	const char delimitate = ',';
	while(std::getline(ss, token, delimitate))
	{
		result.push_back(token);
	}
	return result;
}

Answer::Answer(int id, const int questionId, const std::string& name, const std::string& text, const int votes) : id{ id }, questionId{ questionId }, name{name}, text{text}, votes{votes}
{
}

Answer::Answer(const Answer& entity)
{
	this->id = entity.id;
	this->questionId = entity.questionId;
	this->name = entity.name;
	this->text = entity.text;
	this->votes = entity.votes;
}

bool Answer::operator==(const Answer& otherEntity) const
{
	return (this->id == otherEntity.id);
}

std::vector<std::string> Answer::splitString(const std::string& tapeLine)
{
	std::vector <std::string> result;
	std::stringstream ss(tapeLine);
	std::string token;
	const char delimitate = ',';
	while (std::getline(ss, token, delimitate))
	{
		result.push_back(token);
	}
	return result;
}
