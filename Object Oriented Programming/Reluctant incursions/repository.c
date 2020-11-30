#include "repository.h"
#include <stdlib.h>
#include <stdio.h>

Repository* createRepository()
{
	Repository* repository = (Repository*)malloc(sizeof(Repository));
	if (repository == NULL)
		return NULL;

	repository->dynamicArray = createDynamicArray(10);
	return repository;
}

void destroyRepository(Repository* repository)
{
	destroyDynamicArray(repository->dynamicArray);
	free(repository);
}

int getSize(Repository* repository)
{
	if (repository == NULL)
		return -1;
	return getSizeOfArray(repository->dynamicArray);
}

int add(Repository* repository, TElem supply)
{
	if (repository == NULL)
		return 0;
	if (supply == NULL)
		return 0;
	if (searchElement(repository->dynamicArray, supply) != -1)
		return 0;
	addElement(repository->dynamicArray, supply);
	return 1;
}

int delete(Repository* repository, TElem supply)
{
	if (repository == NULL)
		return 0;
	if (supply == NULL)
		return 0;
	int position = searchElement(repository->dynamicArray, supply);
	if (position == -1)
	{
		destroySupply(supply);
		return 0;
	}
	TElem productToDestroy = getElementFromPosition(repository->dynamicArray, position);
	destroySupply(productToDestroy);
	deleteElement(repository->dynamicArray, position);
	return 1;
}

void update(Repository* repository, TElem supply)
{
	if (repository == NULL)
		return;
	if (supply == NULL)
		return;
	updateElement(repository->dynamicArray, supply, searchElement(repository->dynamicArray, supply));
}

DynamicArray* getAllElements(Repository* repository)
{
	if (repository == NULL)
		return NULL;
	DynamicArray* newArray = createDynamicArray(getSizeOfArray(repository->dynamicArray));
	int index;
	TElem supply;
	TElem currentElement;
	for (index = 0; index < getSizeOfArray(repository->dynamicArray); index++)
	{
		currentElement = getElementFromPosition(repository->dynamicArray, index);
		supply = createSupply(getLocationCode(currentElement), getStoreType(currentElement), getSupplyType(currentElement), getStoreLockComplexity(currentElement));
		addElement(newArray, supply);
	}
	return newArray;
}