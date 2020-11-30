#include "Service.h"
#include <iostream>

void Service::addService(const std::string& title, const std::string& section, int month, int day, int year, int accessCount, const std::string& footagePreview)
{
	Date date{ month, day, year };
	Tape tape{ title, section, date, accessCount, footagePreview };
	ValidateTape::validateTape(tape);
	this->repository.add(tape);
	std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoAdd>(tape, repository);
	this->undoModeA.push_back(action);
	this->notify();
}

void Service::deleteService(const std::string& title)
{
	Date date{};
	Tape tape{ title, "", date, 0, "" };
	Tape currentTape = this->repository.search(tape);
	this->repository.deleteElement(tape);
	std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoRemove>(currentTape, repository);
	this->undoModeA.push_back(action);
	this->notify();
}

void Service::updateService(const std::string& title, const std::string& newSection, int newMonth, int newDay, int newYear, int newAccessCount, const std::string& newFootagePreview)
{
	Date newDate{ newMonth, newDay, newYear };
	Tape tape{ title, newSection, newDate, newAccessCount, newFootagePreview };
	ValidateTape::validateTape(tape);
	Tape oldTape = this->repository.search(tape);
	this->repository.update(tape);
	std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoUpdate>(oldTape, tape, repository);
	this->undoModeA.push_back(action);
	this->notify();
}

std::vector<Tape> Service::getAllElements()
{
	return this->repository.getAll();
}

/*void Service::updateFileLocation(std::string command)
{
	this->repository.setFilePath(command);
}*/

void Service::undoLastActionModeA()
{
	if (this->undoModeA.empty())
		throw ValidationException{ "No more undos left!\n" };
	this->undoModeA.back()->executeUndo();
	this->redoModeA.push_back(this->undoModeA.back());
	this->undoModeA.pop_back();
	this->notify();
	// add on redo
}

void Service::redoLastActionModeA()
{
	if (this->redoModeA.empty())
		throw ValidationException{ "No more redos left!\n" };
	this->redoModeA.back()->executeRedo();
	this->undoModeA.push_back(this->redoModeA.back());
	this->redoModeA.pop_back();
	this->notify();
	// add on undo
}


void Service::addTapeOnWatchList(const std::string& title)
{
	std::vector<Tape> dynamicVector = this->repository.getAll();
	for(auto& element: dynamicVector)
		if (element.getTitle() == title)
		{
			this->watchList.add(element);
			std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoAdd>(element, watchList);
			this->undoModeB.push_back(action);
			this->notify();
			return;
		}
}

Tape Service::next(int &position)
{
	if (position == this->repository.getAll().size())
		position = 0;

	return this->repository.getAll()[position++];
}

std::vector<Tape> Service::list(const std::string& section, int accessCount)
{
	std::vector<Tape> allElements = this->repository.getAll();
	std::vector<Tape> requiredList;
	for (auto& element : allElements)
		if (element.getSection() == section && element.getAccessCount() < accessCount)
			requiredList.push_back(element);
	return requiredList;
}

void Service::myList()
{
	this->watchList.getWatchList();
}

/*void Service::updateMyFileLocationWatchList(std::string command)
{
	this->watchList.setFilePath(command);
}*/

void Service::undoLastActionModeB()
{
	if (this->undoModeB.empty())
		throw ValidationException{ "No more undos left!\n" };
	this->undoModeB.back()->executeUndo();
	this->redoModeB.push_back(this->undoModeB.back());
	this->undoModeB.pop_back();
	this->notify();
	//add on undo
}

void Service::redoLastActionModeB()
{
	if (this->redoModeB.empty())
		throw ValidationException{ "No more redos left!\n" };
	this->redoModeB.back()->executeRedo();
	this->undoModeB.push_back(this->redoModeB.back());
	this->redoModeB.pop_back();
	this->notify();
	//add on redo
}
