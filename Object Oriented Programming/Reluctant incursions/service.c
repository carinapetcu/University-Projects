#include "service.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Service* createService(Repository* repository, Stack* undo, Stack* redo)
{
	Service* service = (Service*)malloc(sizeof(Service));
	if (service == NULL)
		return NULL;
	if (repository == NULL)
		return NULL;
	service->repository = repository;
	service->undo = undo;
	service->redo = redo;
	return service;
}

void destroyService(Service* service)
{
	destroyStack(service->redo);
	destroyStack(service->undo);
	destroyRepository(service->repository);
	free(service);
}

int addSupply(Service* service, int locationCode, char* storeType, char* supplyType, int storeLockComplexity)
{
	if (service == NULL)
		return 0;
	Supply* supply = createSupply(locationCode, storeType, supplyType, storeLockComplexity);
	int isAdded = add(service->repository, supply);
	if (isAdded == 0)
		return 0;
	Supply* copyOfSupplyUndo = createSupply(locationCode, storeType, supplyType, storeLockComplexity);
	TElemUndoRedo elementUndo = createUndoRedo("remove", copyOfSupplyUndo);
	push(service->undo, elementUndo);
	return isAdded;
}

void updateSupply(Service* service, int locationCode, char* newStoreType, char* newSupplyType, int newStoreLockComplexity)
{
	if (service == NULL)
		return;
	Supply* newSupply = createSupply(locationCode, newStoreType, newSupplyType, newStoreLockComplexity);

	DynamicArray* allElements = getAllElements(service->repository);
	int index;
	TElem supplyUndo;

	TElem currentElement;
	for (index = 0; index < getSizeOfArray(allElements); index++)
	{
		currentElement = getElementFromPosition(allElements, index);
		if (getLocationCode(currentElement) == locationCode)
		{
			supplyUndo = createSupply(getLocationCode(currentElement), getStoreType(currentElement), getSupplyType(currentElement), getStoreLockComplexity(currentElement));
			TElemUndoRedo elementUndo = createUndoRedo("update", supplyUndo);
			push(service->undo, elementUndo);
		}
	}
	destroyDynamicArray(allElements);

	update(service->repository, newSupply);
}

int deleteSupply(Service* service, int locationCode)
{
	if (service == NULL)
		return 0;
	Supply* newSupply = createSupply(locationCode, "", "", -1);
	
	DynamicArray* allElements = getAllElements(service->repository);
	int index;
	TElem supplyUndo;
	TElem currentElement;
	for (index = 0; index < getSizeOfArray(allElements); index++)
	{
		currentElement = getElementFromPosition(allElements, index);
		if (getLocationCode(currentElement) == locationCode)
		{
			supplyUndo = createSupply(getLocationCode(currentElement), getStoreType(currentElement), getSupplyType(currentElement), getStoreLockComplexity(currentElement));
			TElemUndoRedo elementUndo = createUndoRedo("add", supplyUndo);
			push(service->undo, elementUndo);
		}
	}
	destroyDynamicArray(allElements);
	int wasDeleted = delete(service->repository, newSupply);
	destroySupply(newSupply);
	
	if (wasDeleted == 0)
	{
		TElemUndoRedo resultUndo = pop(service->undo);
		destroyUndoRedo(resultUndo);
	}
	
	return wasDeleted;
}

DynamicArray* listSupplies(Service* service)
{
	if(service == NULL)
		return NULL;
	return getAllElements(service->repository);
}

DynamicArray* listSuppliesBySupplyType(Service* service, char* supplyType)
{
	if (service == NULL)
		return NULL;
	DynamicArray* allElements = getAllElements(service->repository);
	DynamicArray* newArray = createDynamicArray(getSizeOfArray(allElements));
	int index;
	TElem supply;
	TElem currentElement;
	for (index = 0; index < getSizeOfArray(allElements); index++)
	{
		currentElement = getElementFromPosition(allElements, index);
		if (strcmp(supplyType, getSupplyType(currentElement)) == 0)
		{
			supply = createSupply(getLocationCode(currentElement), getStoreType(currentElement), getSupplyType(currentElement), getStoreLockComplexity(currentElement));
			addElement(newArray, supply);
		}
	}
	destroyDynamicArray(allElements);
	return newArray;
}

DynamicArray* listSuppliesByStoreLockComplexity(Service* service, int maximumStoreLockComplexity)
{
	if (service == NULL)
		return NULL;
	DynamicArray* allElements = getAllElements(service->repository);
	DynamicArray* newArray = createDynamicArray(getSizeOfArray(allElements));
	int index;
	TElem supply;
	TElem currentElement;
	for (index = 0; index < getSizeOfArray(allElements); index++)
	{
		currentElement = getElementFromPosition(allElements, index);
		if (getStoreLockComplexity(currentElement) <= maximumStoreLockComplexity)
		{
			supply = createSupply(getLocationCode(currentElement), getStoreType(currentElement), getSupplyType(currentElement), getStoreLockComplexity(currentElement));
			addElement(newArray, supply);
		}
	}
	destroyDynamicArray(allElements);
	int index1;
	int index2;
	for (index1 = 0; index1 < getSizeOfArray(newArray) - 1; index1++)
	{
		for (index2 = index1 + 1; index2 < getSizeOfArray(newArray); index2++)
		{
			if (strcmp(getStoreType(getElementFromPosition(newArray, index1)), getStoreType(getElementFromPosition(newArray, index2))) > 0)
				swapElements(newArray, index1, index2);
		}
	}
	return newArray;
}

int undoService(Service* service)
{
	if (getSizeOfStack(service->undo) <= 0)
		return 0;
	else
	{
		TElemUndoRedo result = pop(service->undo);
		TElem newSupply = createSupply(getLocationCode(getSupply(result)),
			getStoreType(getSupply(result)),
			getSupplyType(getSupply(result)),
			getStoreLockComplexity(getSupply(result)));
		if (strcmp(getAction(result), "remove") == 0)
		{
			TElem supplyRedo = createSupply(getLocationCode(getSupply(result)),
				getStoreType(getSupply(result)),
				getSupplyType(getSupply(result)),
				getStoreLockComplexity(getSupply(result)));
			TElemUndoRedo elementRedo = createUndoRedo("add", supplyRedo);
			push(service->redo, elementRedo);
			delete(service->repository, newSupply);
			destroySupply(newSupply);
		}
		else
		{
			if (strcmp(getAction(result), "add") == 0)
			{
				TElem supplyRedo = createSupply(getLocationCode(getSupply(result)),
					getStoreType(getSupply(result)),
					getSupplyType(getSupply(result)),
					getStoreLockComplexity(getSupply(result)));
				TElemUndoRedo elementRedo = createUndoRedo("remove", supplyRedo);
				push(service->redo, elementRedo);
				add(service->repository, newSupply);
			}
			else
				if (strcmp(getAction(result), "update") == 0)
				{
					DynamicArray* allElements = getAllElements(service->repository);
					int index;
					TElem supplyRedo;
					TElem currentElement;
					for (index = 0; index < getSizeOfArray(allElements); index++)
					{
						currentElement = getElementFromPosition(allElements, index);
						if (getLocationCode(currentElement) == getLocationCode(getSupply(result)))
						{
							supplyRedo = createSupply(getLocationCode(currentElement), getStoreType(currentElement), getSupplyType(currentElement), getStoreLockComplexity(currentElement));
							TElemUndoRedo elementRedo = createUndoRedo("update", supplyRedo);
							push(service->redo, elementRedo);
						}
					}
					destroyDynamicArray(allElements);
					update(service->repository, newSupply);
				}
		}
		destroyUndoRedo(result);
		return 1;
	}
}

int redoService(Service* service)
{
	if (getSizeOfStack(service->redo) <= 0)
		return 0;
	else
	{
		TElemUndoRedo result = pop(service->redo);
		TElem newSupply = createSupply(getLocationCode(getSupply(result)),
			getStoreType(getSupply(result)),
			getSupplyType(getSupply(result)),
			getStoreLockComplexity(getSupply(result)));
		if (strcmp(getAction(result), "remove") == 0)
		{
			TElem supplyUndo = createSupply(getLocationCode(getSupply(result)),
				getStoreType(getSupply(result)),
				getSupplyType(getSupply(result)),
				getStoreLockComplexity(getSupply(result)));
			TElemUndoRedo elementUndo = createUndoRedo("add", supplyUndo);
			push(service->undo, elementUndo);
			delete(service->repository, newSupply);
			destroySupply(newSupply);
		}
		else
		{
			if (strcmp(getAction(result), "add") == 0)
			{
				TElem supplyUndo = createSupply(getLocationCode(getSupply(result)),
					getStoreType(getSupply(result)),
					getSupplyType(getSupply(result)),
					getStoreLockComplexity(getSupply(result)));
				TElemUndoRedo elementUndo = createUndoRedo("remove", supplyUndo);
				push(service->redo, elementUndo);
				add(service->repository, newSupply);
			}
			else
				if (strcmp(getAction(result), "update") == 0)
				{
					DynamicArray* allElements = getAllElements(service->repository);
					int index;
					TElem supplyUndo;
					TElem currentElement;
					for (index = 0; index < getSizeOfArray(allElements); index++)
					{
						currentElement = getElementFromPosition(allElements, index);
						if (getLocationCode(currentElement) == getLocationCode(getSupply(result)))
						{
							supplyUndo = createSupply(getLocationCode(currentElement), getStoreType(currentElement), getSupplyType(currentElement), getStoreLockComplexity(currentElement));
							TElemUndoRedo elementUndo = createUndoRedo("update", supplyUndo);
							push(service->undo, elementUndo);
						}
					}
					destroyDynamicArray(allElements);
					update(service->repository, newSupply);
				}
		}
		destroyUndoRedo(result);
		return 1;
	}
}