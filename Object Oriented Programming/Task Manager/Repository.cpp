#include "Repository.h"

void Repository::add(const TElement& tape)
{
	std::vector<TElement>::iterator found;
	found = std::find(this->tapes.begin(), this->tapes.end(), tape);
	if (found == this->tapes.end())
	{
		this->tapes.push_back(tape);
	}
	else
	{
		throw RepositoryException("Tape already added!\n");
	}
}

void Repository::deleteElement(const TElement& tape)
{
	std::vector<TElement>::iterator found;
	found = std::find(this->tapes.begin(), this->tapes.end(), tape);
	if (found == this->tapes.end())
	{
		throw RepositoryException("Tape does not exist!\n");
	}
	else
	{
		this->tapes.erase(found);
	}
}

void Repository::update(const TElement& tape)
{
	std::vector<TElement>::iterator found;
	found = std::find(this->tapes.begin(), this->tapes.end(), tape);
	if (found == this->tapes.end())
	{
		throw RepositoryException("Tape does not exist!\n");
	}
	else
	{
		this->tapes.erase(found);
		this->tapes.push_back(tape);
	}
}

int Repository::getSizeOfRepository()
{
	return this->tapes.size();
}

std::vector<TElement> Repository::getAll()
{
	return this->tapes;
}

void FileRepository::readFromFile()
{
	std::ifstream fileIn(this->filePath);
	if (!fileIn.is_open())
		createFile();
	this->tapes.clear();
	TElement currentTape;
	while (fileIn >> currentTape)
	{
		this->tapes.push_back(currentTape);
	}
	fileIn.close();
}
void FileRepository::writeToFile()
{
	std::ofstream fileOut(this->filePath, std::ios::in);
	for (auto& element : this->tapes)
		fileOut << element;
	fileOut.close();
	this->tapes.clear();
}

void FileRepository::createFile()
{
	std::ofstream fileOut(this->filePath, std::ios::app);
	fileOut.close();
	std::ifstream fileIn(this->filePath);
}

void FileRepository::add(const TElement& tape)
{
	this->readFromFile();
	Repository::add(tape);
	this->writeToFile();

}

void FileRepository::deleteElement(const TElement& tape)
{
	this->readFromFile();
	Repository::deleteElement(tape);
	this->writeToFile();
}

void FileRepository::update(const TElement& tape)
{
	this->readFromFile();
	Repository::update(tape);
	this->writeToFile();
}

int FileRepository::getSizeOfRepository()
{
	this->readFromFile();
	return Repository::getSizeOfRepository();
}

std::vector<TElement> FileRepository::getAll()
{
	this->readFromFile();
	return Repository::getAll();
}


