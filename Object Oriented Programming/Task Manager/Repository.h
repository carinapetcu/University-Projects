#pragma once
#include <vector>
#include <algorithm>
#include "Tape.h"
#include "Exceptions.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

typedef Task TElement;

class Repository
{
protected:
	std::vector<TElement> tapes;

public:
	virtual void add(const TElement& tape);
	virtual void deleteElement(const TElement& tape);
	virtual void update(const TElement& tape);
	virtual int getSizeOfRepository();
	virtual std::vector<TElement> getAll();
	virtual ~Repository() {};
};



class FileRepository : public Repository
{
protected:
	std::string filePath;

public:
	FileRepository() {};
	FileRepository(std::string& fileName): filePath(fileName) {};

	void setFilePath(std::string& newFilePath) { this->filePath.assign(newFilePath);};
	void createFile();

	void add(const TElement& tape) override;
	void deleteElement(const TElement& tape) override;
	void update(const TElement& tape) override;
	int getSizeOfRepository() override;
	std::vector<TElement> getAll() override;
	virtual void readFromFile();
	virtual void writeToFile();
};

