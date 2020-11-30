#pragma once
#include "undoRedo.h"
#include "domain.h"

typedef UndoRedo* TElemUndoRedo;

typedef struct 
{
	int capacity;
	int length;
	TElemUndoRedo* elements;
}Stack;

Stack* createStack(int capacity);
void destroyStack(Stack* stack);

int getSizeOfStack(Stack* stack);
void push(Stack* stack, TElemUndoRedo undoRedo);
TElemUndoRedo pop(Stack* stack);
void resize(Stack* stack);