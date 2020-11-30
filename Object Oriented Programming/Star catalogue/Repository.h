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
	std::vector<Star> entities;

public:
	virtual void add(const Star& entity);
	virtual void deleteElement(const Star& entity);
	virtual void update(const Star& entity);
	virtual int getSizeOfRepository();
	virtual std::vector<Star> getAll();
	virtual ~Repository() {};
};

template <typename TElement>
void Repository<TElement>::add(const Star& entity)
{
	std::vector<TElement>::iterator found;
	found = std::find(this->entities.begin(), this->entities.end(), entity);
	if (found == this->entities.end())
	{
		this->entities.push_back(entity);
	}
	else
	{
		throw RepositoryException("Entity already added!\n");
	}
}

template <typename TElement>
void Repository<TElement>::deleteElement(const Star& entity)
{
	std::vector<TElement>::iterator found;
	found = std::find(this->entities.begin(), this->entities.end(), entity);
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
void Repository<TElement>::update(const Star& entity)
{
	std::vector<TElement>::iterator found;
	found = std::find(this->entities.begin(), this->entities.end(), entity);
	if (found == this->entities.end())
	{
		throw RepositoryException("Entity does not exist!\n");
	}
	else
	{
		this->entities.erase(found);
		this->entities.push_back(entity);
	}
}

template <typename TElement>
int Repository<TElement>::getSizeOfRepository()
{
	return this->entities.size();
}

template <typename TElement>
std::vector<Star> Repository<TElement>::getAll()
{
	std::sort(this->entities.begin(), this->entities.end(), [](Star& firstStar, Star& secondStar) {return firstStar.getConstellation() < secondStar.getConstellation(); });
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

	void add(const Star& entity) override;
	void deleteElement(const Star& entity) override;
	void update(const Star& entity) override;
	int getSizeOfRepository() override;
	std::vector<Star> getAll() override;
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
	Star currentTape;
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
	std::ofstream fileOut(this->filePath);
	fileOut.close();
	std::ifstream fileIn(this->filePath);
}


template <typename TElement>
void FileRepository<TElement>::add(const Star& entity)
{
	this->readFromFile();
	Repository<TElement>::add(entity);
	this->writeToFile();

}

template <typename TElement>
void FileRepository<TElement>::deleteElement(const Star& entity)
{
	this->readFromFile();
	Repository<TElement>::deleteElement(entity);
	this->writeToFile();
}

template <typename TElement>
void FileRepository<TElement>::update(const Star& entity)
{
	this->readFromFile();
	Repository<TElement>::update(entity);
	this->writeToFile();
}

template <typename TElement>
int FileRepository<TElement>::getSizeOfRepository()
{
	this->readFromFile();
	return Repository<TElement>::getSizeOfRepository();
}

template <typename TElement>
std::vector<Star> FileRepository<TElement>::getAll()
{
	this->readFromFile();
	std::vector<Star> allStars = Repository<TElement>::getAll();
	this->writeToFile();
	return allStars;

}
