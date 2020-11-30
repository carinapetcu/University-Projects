#pragma once
#include "UndoRedoAction.h"
#include "Tape.h"
#include "Repository.h"

class UndoRedoUpdate :
	public UndoRedoAction
{
private:
	Tape oldTape;
	Tape newTape;
	Repository<Tape>& repository;

public:
	UndoRedoUpdate(const Tape& oldTape, const Tape& newTape, Repository<Tape>& newRepository) : oldTape(oldTape), newTape(newTape), repository(newRepository) {};
	void executeUndo() override;
	void executeRedo() override;
};

