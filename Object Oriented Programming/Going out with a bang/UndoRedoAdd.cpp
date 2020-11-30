#include "UndoRedoAdd.h"

void UndoRedoAdd::executeUndo()
{
	repository.deleteElement(addedTape);
}

void UndoRedoAdd::executeRedo()
{
	repository.add(addedTape);
}
