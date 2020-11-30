#pragma once
#include "domain.h"

typedef Supply* TElem;

typedef struct
{
	char* action;
	TElem supply;
}UndoRedo;

UndoRedo* createUndoRedo(char* action, TElem supply);
void destroyUndoRedo(UndoRedo* undoRedo);

char* getAction(UndoRedo* undoRedo);
TElem getSupply(UndoRedo* undoRedo);

void setAction(UndoRedo* undoRedo, char* action);
void setSupply(UndoRedo* undoRedo, TElem supply);