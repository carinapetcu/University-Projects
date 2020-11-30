#include "undoRedo.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

UndoRedo* createUndoRedo(char* action, TElem supply)
{
	UndoRedo* undoRedo = (UndoRedo*)malloc(sizeof(UndoRedo));
	if (undoRedo == NULL)
		return NULL;

	undoRedo->action = NULL;
	
	undoRedo->supply = NULL;
	
	setAction(undoRedo, action);
	setSupply(undoRedo, supply);

	return undoRedo;
}

void destroyUndoRedo(UndoRedo* undoRedo)
{
	if (undoRedo == NULL)
		return;
	destroySupply(undoRedo->supply);
	free(undoRedo->action);
	free(undoRedo);
}

char* getAction(UndoRedo* undoRedo)
{
	if (undoRedo == NULL)
		return NULL;
	return undoRedo->action;
}

TElem getSupply(UndoRedo* undoRedo)
{
	if (undoRedo == NULL)
		return NULL;
	return undoRedo->supply;
}

void setAction(UndoRedo* undoRedo, char* action)
{
	if (undoRedo == NULL)
		return;
	if (undoRedo->action != NULL)
	{
		free(undoRedo->action);
		undoRedo->action = NULL;
	}
	undoRedo->action = (char*)malloc(sizeof(char) * (strlen(action) + 1));
	strcpy(undoRedo->action, action);
}

void setSupply(UndoRedo* undoRedo, TElem supply)
{
	if (undoRedo == NULL)
		return;
	if (undoRedo->supply != NULL)
	{
		destroySupply(undoRedo->supply);
		undoRedo->supply = NULL;
	}
	undoRedo->supply = createSupply(getLocationCode(supply), getStoreType(supply), getSupplyType(supply), getStoreLockComplexity(supply));
	destroySupply(supply);
}