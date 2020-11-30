#include "dynamicArray.h"
#include <stdlib.h>
#include <stdio.h>

DynamicArray* createDynamicArray(int capacity)
{
	DynamicArray* dynamicArray = (DynamicArray*)malloc(sizeof(DynamicArray));
	if (dynamicArray == NULL)
		return NULL;

	dynamicArray->capacity = capacity;
	dynamicArray->length = 0;

	dynamicArray->elements = (TElem*)malloc(sizeof(TElem) * capacity);
	if (dynamicArray->elements == NULL)
		return NULL;
	return dynamicArray;
}


void destroyDynamicArray(DynamicArray* dynamicArray)
{
	if (dynamicArray == NULL)
		return;
	int index;
	for (index = 0; index < dynamicArray->length; index++)
		destroySupply(dynamicArray->elements[index]);
	free(dynamicArray->elements);
	free(dynamicArray);
}


void resizeDynamicArray(DynamicArray* dynamicArray)
{
	if (dynamicArray == NULL)
		return;
	dynamicArray->capacity *= 2;

	TElem* auxiliaryArray = (TElem*)malloc(sizeof(TElem) * dynamicArray->capacity);
	if (auxiliaryArray == NULL)
		return;

	int index;
	for (index = 0; index < dynamicArray->length; index++)
		auxiliaryArray[index] = dynamicArray->elements[index];

	free(dynamicArray->elements);
	dynamicArray->elements = auxiliaryArray;
}

void addElement(DynamicArray* dynamicArray, TElem element)
{
	if (dynamicArray == NULL)
		return;
	if (element == NULL)
		return;
	if (dynamicArray->length == dynamicArray->capacity)
		resizeDynamicArray(dynamicArray);
	dynamicArray->elements[dynamicArray->length++] = element;
}

int searchElement(DynamicArray* dynamicArray, TElem element)
{
	if (dynamicArray == NULL)
		return -1;
	if (element == NULL)
		return -1;
	int index;
	for (index = 0; index < dynamicArray->length; index++)
		if (getLocationCode(dynamicArray->elements[index]) == getLocationCode(element))
			return index;
	return -1;
}

void deleteElement(DynamicArray* dynamicArray, int position)
{
	if (dynamicArray == NULL)
		return;
	if (position < 0 || position >= dynamicArray->length)
		return;
	int index;
	if (dynamicArray->length > 0)
	{
		dynamicArray->length--;
		for (index = position; index < dynamicArray->length; index++)
			dynamicArray->elements[index] = dynamicArray->elements[index + 1];
	}
}

void updateElement(DynamicArray* dynamicArray, TElem newElement, int position)
{
	if (dynamicArray == NULL)
		return;
	if (newElement == NULL)
		return;
	destroySupply(dynamicArray->elements[position]);
	dynamicArray->elements[position] = newElement;

}

int getSizeOfArray(DynamicArray* dynamicArray)
{
	if (dynamicArray == NULL)
		return -1;
	return dynamicArray->length;
}

TElem getElementFromPosition(DynamicArray* dynamicArray, int position)
{
	if (dynamicArray == NULL)
		return NULL;
	return dynamicArray->elements[position];
}

void swapElements(DynamicArray* dynamicArray, int positionFirstElement, int positionSecondElement)
{
	TElem auxiliaryElement = dynamicArray->elements[positionFirstElement];
	dynamicArray->elements[positionFirstElement] = dynamicArray->elements[positionSecondElement];
	dynamicArray->elements[positionSecondElement] = auxiliaryElement;
}