#include "UndoRedoRemove.h"

void UndoRedoRemove::executeUndo()
{
	repository.add(removedTape);
}

void UndoRedoRemove::executeRedo()
{
	repository.deleteElement(removedTape);
}
