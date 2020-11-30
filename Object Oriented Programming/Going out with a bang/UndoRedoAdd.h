#pragma once
#include "UndoRedoAction.h"
#include "Repository.h"
#include "Tape.h"

class UndoRedoAdd :
	public UndoRedoAction
{
private:
	Tape addedTape;
	Repository<Tape>& repository;

public:
	UndoRedoAdd(const Tape& tape, Repository<Tape>& newRepository) : addedTape(tape), repository(newRepository) {};
	void executeUndo() override;
	void executeRedo() override;
};

