#pragma once
#include "domain.h"
#include "dynamicArray.h"
#include "stack.h"

typedef struct {
	DynamicArray* dynamicArray;
}Repository;

Repository* createRepository();
void destroyRepository(Repository* repository);

int add(Repository* repository, TElem supply);
int delete(Repository* repository, TElem supply);
void update(Repository* repository, TElem supply);
DynamicArray* getAllElements(Repository* repository);
int getSize(Repository* repository);