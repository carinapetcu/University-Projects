#pragma once
class UndoRedoAction
{
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
	virtual ~UndoRedoAction() {};
};

