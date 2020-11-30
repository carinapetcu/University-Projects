#include "stack.h"
#include <stdlib.h>

Stack* createStack(int capacity)
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	if (stack == NULL)
		return NULL;

	stack->length = 0;
	stack->capacity = capacity;

	stack->elements = (TElemUndoRedo*)malloc(sizeof(TElemUndoRedo) * capacity);
	if (stack->elements == NULL)
		return NULL;

	return stack;
}

void destroyStack(Stack* stack)
{
	if (stack == NULL)
		return;
	int index;
	for (index = 0; index < stack->length; index++)
		destroyUndoRedo(stack->elements[index]);
	free(stack->elements);
	free(stack);
}

int getSizeOfStack(Stack* stack)
{
	if (stack == NULL)
		return -1;
	return stack->length;
}

void resize(Stack* stack)
{
	if (stack == NULL)
		return NULL;
	stack->capacity *= 2;
	TElemUndoRedo* newUndoRedo = (TElem*)malloc(sizeof(TElemUndoRedo) * stack->capacity);
	int index;
	for (index = 0; index < stack->length; index++)
		newUndoRedo[index] = stack->elements[index];
	free(stack->elements);
	stack->elements = newUndoRedo;
}

void push(Stack* stack, TElemUndoRedo undoRedo)
{
	if (stack == NULL)
		return;
	if (undoRedo == NULL)
		return;
	
	if (stack->length == stack->capacity)
		resize(stack);
	
	stack->elements[stack->length++] = undoRedo;
}

TElemUndoRedo pop(Stack* stack)
{
	if (stack == NULL)
		return NULL;

	TElemUndoRedo lastElement = stack->elements[stack->length - 1];

	if (stack->length > 0)
	{
		stack->length--;
	}
	return lastElement;
}