#pragma once
#include "UndoRedoAction.h"
#include "Tape.h"
#include "Repository.h"

class UndoRedoRemove :
	public UndoRedoAction
{
private:
	Tape removedTape;
	Repository<Tape>& repository;

public:
	UndoRedoRemove(const Tape& tape, Repository<Tape>& newRepository) : removedTape(tape), repository(newRepository) {};
	void executeUndo() override;
	void executeRedo() override;
};

