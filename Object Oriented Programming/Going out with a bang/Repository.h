#pragma once
#include <vector>
#include <algorithm>
#include "Tape.h"
#include "Exceptions.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

template <typename TElement>
class Repository
{
protected:
	std::vector<TElement> tapes;

public:
	virtual void add(const TElement& tape);
	virtual void deleteElement(const TElement& tape);
	virtual void update(const TElement& tape);
	virtual Tape search(const TElement& tape);
	virtual int getSizeOfRepository();
	virtual void getWatchList() {};
	virtual std::vector<TElement> getAll();
	virtual ~Repository() {};
};

template<typename TElement>
void Repository<TElement>::add(const TElement& tape)
{
	std::vector<Tape>::iterator found;
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

template<typename TElement>
void Repository<TElement>::deleteElement(const TElement& tape)
{
	std::vector<Tape>::iterator found;
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

template<typename TElement>
void Repository<TElement>::update(const TElement& tape)
{
	std::vector<Tape>::iterator found;
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

template<typename TElement>
Tape Repository<TElement>::search(const TElement& tape)
{
	for (auto& currentTape : tapes)
		if (tape == currentTape)
			return currentTape;
	throw RepositoryException("Tape does not exist!\n");
}

template<typename TElement>
int Repository<TElement>::getSizeOfRepository()
{
	return this->tapes.size();
}

template<typename TElement>
std::vector<TElement> Repository<TElement>::getAll()
{
	return this->tapes;
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

	void add(const TElement& tape) override;
	void deleteElement(const TElement& tape) override;
	void update(const TElement& tape) override;
	Tape search(const TElement& tape) override;
	int getSizeOfRepository() override;
	std::vector<TElement> getAll() override;
	virtual void readFromFile();
	virtual void writeToFile();
	virtual void getWatchList();
};

template<typename TElement>
void FileRepository<TElement>::readFromFile()
{
	std::ifstream fileIn(this->filePath);
	if (!fileIn.is_open())
		createFile();
	this->tapes.clear();
	Tape currentTape;
	while (fileIn >> currentTape)
	{
		this->tapes.push_back(currentTape);
	}
	fileIn.close();
}

template<typename TElement>
void FileRepository<TElement>::writeToFile()
{
	std::ofstream fileOut(this->filePath);
	for (auto& element : this->tapes)
		fileOut << element;
	fileOut.close();
	this->tapes.clear();
}

template<typename TElement>
inline void FileRepository<TElement>::getWatchList()
{
}

template<typename TElement>
void FileRepository<TElement>::createFile()
{
	std::ofstream fileOut(this->filePath, std::ios::app);
	fileOut.close();
	std::ifstream fileIn(this->filePath);
}

template<typename TElement>
void FileRepository<TElement>::add(const TElement& tape)
{
	this->readFromFile();
	Repository<TElement>::add(tape);
	this->writeToFile();

}

template<typename TElement>
void FileRepository<TElement>::deleteElement(const TElement& tape)
{
	this->readFromFile();
	Repository<TElement>::deleteElement(tape);
	this->writeToFile();
}

template<typename TElement>
void FileRepository<TElement>::update(const TElement& tape)
{
	this->readFromFile();
	Repository<TElement>::update(tape);
	this->writeToFile();
}

template<typename TElement>
Tape FileRepository<TElement>::search(const TElement& tape)
{
	this->readFromFile();
	return Repository<TElement>::search(tape);
}

template<typename TElement>
int FileRepository<TElement>::getSizeOfRepository()
{
	this->readFromFile();
	return Repository<TElement>::getSizeOfRepository();
}

template<typename TElement>
std::vector<TElement> FileRepository<TElement>::getAll()
{
	this->readFromFile();
	return Repository<TElement>::getAll();
}

template <typename TElement>
class CSVWatchList : public FileRepository<TElement>
{
private:
	std::string fileName;

public:
	CSVWatchList(std::string& newFileName) : fileName{ newFileName } {};
	void writeToFile() override;
	void readFromFile() override;
	void getWatchList();
};

template <typename TElement>
void CSVWatchList<TElement>::writeToFile()
{
	std::ostringstream out;
	out << "Title,Section,dateOfCreation,accessCount,footagePreview\n";
	for (auto& element : this->tapes)
	{
		out << element;
	}
	std::ofstream fileOut(this->fileName, std::ios::trunc | std::ios::in);
	fileOut << out.str();
	fileOut.close();
	this->tapes.clear();
}

template <typename TElement>
void CSVWatchList<TElement>::readFromFile()
{
	std::ifstream fileIn(this->fileName);
	this->tapes.clear();
	if (fileIn.is_open())
	{
		std::string firstLine;
		std::getline(fileIn, firstLine);
		Tape currentTape;
		while (fileIn >> currentTape)
		{
			if (!(currentTape == Tape{ "", "", Date{0,0,0},0, "" }))
				this->tapes.push_back(currentTape);
		}
		fileIn.close();
	}
}

template <typename TElement>
void CSVWatchList<TElement>::getWatchList()
{
	this->readFromFile();
	this->writeToFile();
	std::stringstream systemCommand;
	systemCommand << "\"";
	systemCommand << "\"" << "C:\\Windows\\notepad.exe" << "\" ";
	systemCommand << "\"" << this->fileName << "\"";
	systemCommand << "\"";
	system(systemCommand.str().c_str());
}


template <typename TElement>
class HTMLWatchList : public FileRepository<TElement>
{
private:
	std::string fileName;

public:
	HTMLWatchList(std::string& newFileName) : fileName{ newFileName } {};
	void writeToFile() override;
	void readFromFile() override;
	void getWatchList();
};

template <typename TElement>
void HTMLWatchList<TElement>::writeToFile()
{
	std::ostringstream out;
	std::ofstream fileOut(this->fileName);
	out << "<!DOCTYPE html>\n<html><head><title>Watchlist</title></head><body>\n";
	out << "<table border=\"1\">\n";
	out << "<tr><td>Title</td><td>Section</td><td>dateOfCreation</td><td>accessCount</td><td>footagePreview</td></tr>\n";
	for (const Tape& element : tapes)
	{
		out << "<tr>\n";
		out << "<td>" << element.getTitle() << "</td>\n";
		out << "<td>" << element.getSection() << "</td>\n";
		out << "<td>" << element.getDate().getMonth() << "-" << element.getDate().getDay() << "-" << element.getDate().getYear() << "</td>\n";
		out << "<td>" << element.getAccessCount() << "</td>\n";
		out << "<td><a href=" << element.getFootagePreview() << ">" << element.getFootagePreview() << "</a></td>\n";
		out << "</tr>\n";
	}
	out << "</table></body></html>";
	fileOut << out.str();
	fileOut.close();
	this->tapes.clear();
}

template <typename TElement>
void HTMLWatchList<TElement>::readFromFile()
{
	std::ifstream fileIn(this->fileName);
	this->tapes.clear();
	if (fileIn.is_open())
	{
		std::string firstLines;
		std::getline(fileIn, firstLines);
		std::getline(fileIn, firstLines);
		std::getline(fileIn, firstLines);
		std::getline(fileIn, firstLines);
		std::string currentLine;

		while (std::getline(fileIn, currentLine))
		{
			std::string lastLine{ "</table></body></html>" };
			if (currentLine.find(lastLine) == std::string::npos)
			{
				std::getline(fileIn, currentLine);

				std::string title = currentLine.substr(4, currentLine.size() - 9);
				std::getline(fileIn, currentLine);
				std::string section = currentLine.substr(4, currentLine.size() - 9);
				std::getline(fileIn, currentLine);
				std::string dateString = currentLine.substr(4, currentLine.size() - 5);
				std::getline(fileIn, currentLine);
				int accessCount = std::stoi(currentLine.substr(4, currentLine.size() - 5));
				std::getline(fileIn, currentLine);
				std::string footagePreview = currentLine.substr(12);
				footagePreview = footagePreview.substr(0, footagePreview.size() - 9);
				footagePreview = footagePreview.substr(0, footagePreview.size() / 2);

				std::size_t positionOfMinus = dateString.find("-");
				int month = stoi(dateString.substr(0, positionOfMinus));
				dateString.erase(0, positionOfMinus + 1);
				positionOfMinus = dateString.find("-");
				int day = stoi(dateString.substr(0, positionOfMinus));
				dateString.erase(0, positionOfMinus + 1);
				int year = stoi(dateString.substr(0));
				Date date{ month, day, year };
				Tape currentTape{ title, section, date, accessCount, footagePreview };
				this->tapes.push_back(currentTape);
				std::getline(fileIn, firstLines);
			}
		}
		fileIn.close();
	}
}

template <typename TElement>
void HTMLWatchList<TElement>::getWatchList()
{
	this->readFromFile();
	this->writeToFile();
	std::stringstream systemCommand;
	systemCommand << "\"";
	systemCommand << "\"" << "C:\\Program Files (x86)\\Google\\Chrome\\Application\\Chrome.exe" << "\" ";
	systemCommand << "\"" << this->fileName << "\"";
	systemCommand << "\"";
	system(systemCommand.str().c_str());
}