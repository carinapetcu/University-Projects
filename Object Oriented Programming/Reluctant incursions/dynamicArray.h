#pragma once
#include "domain.h"

typedef Supply* TElem;

typedef struct {
	TElem* elements;
	int capacity;
	int length;

}DynamicArray;

DynamicArray* createDynamicArray(int capacity);
void destroyDynamicArray(DynamicArray* dynamicArray);
void resizeDynamicArray(DynamicArray* dynamicArray);

void addElement(DynamicArray* dynamicArray, TElem element);
int searchElement(DynamicArray* dynamicArray, TElem element);
void deleteElement(DynamicArray* dynamicArray, int position);
void updateElement(DynamicArray* dynamicArray, TElem newElement, int position);
int getSizeOfArray(DynamicArray* dynamicArray);
TElem getElementFromPosition(DynamicArray* dynamicArray, int position);
void swapElements(DynamicArray* dynamicArray, int positionFirstElement, int positionSecondElement);
