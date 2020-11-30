#pragma once
#include "Repository.h"
#include "Validators.h"
#include "Tape.h"
#include <string>
#include <vector>
#include <memory>
#include "UndoRedoAction.h"
#include "UndoRedoAdd.h"
#include "UndoRedoRemove.h"
#include "UndoRedoUpdate.h"
#include "Observer.h"

class Service : public Subject
{
private:
	Repository<Tape>& repository;
	Repository<Tape>& watchList;
	std::vector<std::shared_ptr<UndoRedoAction>> undoModeA;
	std::vector<std::shared_ptr<UndoRedoAction>> redoModeA;
	std::vector<std::shared_ptr<UndoRedoAction>> undoModeB;
	std::vector<std::shared_ptr<UndoRedoAction>> redoModeB;

public:
	Service(Repository<Tape>& repositoryNew, Repository<Tape>& newWatchList) : repository{ repositoryNew }, watchList{ newWatchList } {};
	~Service() {};

	Repository<Tape>& getWatchList() const { return this->watchList; };

	void addService(const std::string& title, const std::string& section, int month, int day, int year, int accessCount, const std::string& footagePreview);
	void deleteService(const std::string& title);
	void updateService(const std::string& title, const std::string& newSection, int newMonth, int newDay, int newYear, int newAccessCount, const std::string& newFootagePreview);
	std::vector<Tape> getAllElements();
	//void updateFileLocation(std::string command);
	void undoLastActionModeA();
	void redoLastActionModeA();

	void addTapeOnWatchList(const std::string& title);
	Tape next(int &position);
	std::vector<Tape> list(const std::string& section, int accessCount);
	void myList();
	//void updateMyFileLocationWatchList(std::string command);
	void undoLastActionModeB();
	void redoLastActionModeB();
};