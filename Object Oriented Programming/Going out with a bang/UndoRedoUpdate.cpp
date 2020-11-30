#include "UndoRedoUpdate.h"

void UndoRedoUpdate::executeUndo()
{
	repository.update(oldTape);
}

void UndoRedoUpdate::executeRedo()
{
	repository.update(newTape);
}
