#pragma once
#include <vector>
#include <algorithm>
#include "Domain.h"
#include "Exceptions.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

template <typename TElement>
class Repository
{
protected:
	std::vector<TElement> entities;

public:
	virtual void add(const TElement& entity);
	virtual void deleteElement(const TElement& entity);
	virtual void update(const TElement& entity);
	virtual int getSizeOfRepository();
	virtual std::vector<TElement> getAll();
	virtual ~Repository() {};
};

template <typename TElement>
void Repository<TElement>::add(const TElement& tape)
{
	std::vector<TElement>::iterator found;
	found = std::find(this->entities.begin(), this->entities.end(), tape);
	if (found == this->entities.end())
	{
		this->entities.push_back(tape);
	}
	else
	{
		throw RepositoryException("Entity already added!\n");
	}
}

template <typename TElement>
void Repository<TElement>::deleteElement(const TElement& tape)
{
	std::vector<TElement>::iterator found;
	found = std::find(this->entities.begin(), this->entities.end(), tape);
	if (found == this->entities.end())
	{
		throw RepositoryException("Entity does not exist!\n");
	}
	else
	{
		this->entities.erase(found);
	}
}

template <typename TElement>
void Repository<TElement>::update(const TElement& tape)
{
	std::vector<TElement>::iterator found;
	found = std::find(this->entities.begin(), this->entities.end(), tape);
	if (found == this->entities.end())
	{
		throw RepositoryException("Entity does not exist!\n");
	}
	else
	{
		this->entities.erase(found);
		this->entities.push_back(tape);
	}
}

template <typename TElement>
int Repository<TElement>::getSizeOfRepository()
{
	return this->entities.size();
}

template <typename TElement>
std::vector<TElement> Repository<TElement>::getAll()
{
	return this->entities;
}

template <typename TElement>
class FileRepository : public Repository<TElement>
{
protected:
	std::string filePath;

public:
	FileRepository() {};
	FileRepository(std::string& fileName): filePath(fileName) {};

	void setFilePath(std::string& newFilePath) { this->filePath.assign(newFilePath);};
	void createFile();

	void add(const TElement& entity) override;
	void deleteElement(const TElement& entity) override;
	void update(const TElement& entity) override;
	int getSizeOfRepository() override;
	std::vector<TElement> getAll() override;
	virtual void readFromFile();
	virtual void writeToFile();
};

template <typename TElement>
void FileRepository<TElement>::readFromFile()
{
	std::ifstream fileIn(this->filePath);
	if (!fileIn.is_open())
		createFile();
	this->entities.clear();
	TElement currentTape;
	while (fileIn >> currentTape)
	{
		this->entities.push_back(currentTape);
	}
	fileIn.close();
}

template <typename TElement>
void FileRepository<TElement>::writeToFile()
{
	std::ofstream fileOut(this->filePath);
	for (auto& element : this->entities)
		fileOut << element;
	fileOut.close();
	this->entities.clear();
}

template <typename TElement>
void FileRepository<TElement>::createFile()
{
	std::ofstream fileOut(this->filePath, std::ios::app);
	fileOut.close();
	std::ifstream fileIn(this->filePath);
}

template <typename TElement>
void FileRepository<TElement>::add(const TElement& tape)
{
	this->readFromFile();
	Repository<TElement>::add(tape);
	this->writeToFile();

}

template <typename TElement>
void FileRepository<TElement>::deleteElement(const TElement& tape)
{
	this->readFromFile();
	Repository<TElement>::deleteElement(tape);
	this->writeToFile();
}

template <typename TElement>
void FileRepository<TElement>::update(const TElement& tape)
{
	this->readFromFile();
	Repository<TElement>::update(tape);
	this->writeToFile();
}

template <typename TElement>
int FileRepository<TElement>::getSizeOfRepository()
{
	this->readFromFile();
	return Repository<TElement>::getSizeOfRepository();
}

template <typename TElement>
std::vector<TElement> FileRepository<TElement>::getAll()
{
	this->readFromFile();
	return Repository<TElement>::getAll();
}




