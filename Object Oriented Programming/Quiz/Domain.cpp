#include "Domain.h"
std::istream& operator>>(std::istream& istream, Participant& entity)
{
	std::string tapeLine;
	std::getline(istream, tapeLine);
	std::vector<std::string> lineParts;
	if (tapeLine == "")
	{
		return istream;
	}
	lineParts = Participant::splitString(tapeLine);
	entity.name = lineParts[0];
	entity.score = std::stoi(lineParts[1]);
	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Participant& entity)
{
	std::string result;
	result.append(entity.getName());
	result.append(",");
	result.append(std::to_string(entity.getScore()));
	result.append("\n");
	ostream << result;
	return ostream;
}

std::istream& operator>>(std::istream& istream, Question& entity)
{
	std::string tapeLine;
	std::getline(istream, tapeLine);
	std::vector<std::string> lineParts;
	if (tapeLine == "")
	{
		return istream;
	}
	lineParts = Participant::splitString(tapeLine);
	entity.id = std::stoi(lineParts[0]);
	entity.text = lineParts[1];
	entity.correctAnswer = lineParts[2];
	entity.score = std::stoi(lineParts[3]);
	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Question& entity)
{
	std::string result;
	result.append(std::to_string(entity.getId()));
	result.append(",");
	result.append(entity.getText());
	result.append(",");
	result.append(entity.getCorrectAnswer());
	result.append(",");
	result.append(std::to_string(entity.getScore()));
	result.append("\n");
	ostream << result;
	return ostream;
}

Participant::Participant(const Participant& entity)
{
	this->name = entity.name;
	this->score = entity.score;
}

bool Participant::operator==(const Participant& otherEntity) const
{
	return (this->name == otherEntity.name);
}

std::vector<std::string> Participant::splitString(const std::string& tapeLine)
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

Question::Question(const Question& entity)
{
	this->id = entity.id;
	this->text = entity.text;
	this->correctAnswer = entity.correctAnswer;
	this->score = entity.score;
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
	while (std::getline(ss, token, delimitate))
	{
		result.push_back(token);
	}
	return result;
}
