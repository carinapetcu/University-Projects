#pragma once
#include "repository.h"
#include"domain.h"
#include "stack.h"

typedef struct {
	Repository* repository;
	Stack* undo;
	Stack* redo;
}Service;

Service* createService(Repository* repository, Stack* undo, Stack* redo);
void destroyService(Service* service);

int addSupply(Service* service, int locationCode, char* storeType, char* supplyType, int storeLockComplexity);
void updateSupply(Service* service, int locationCode, char* newStoreType, char* newSupplyType, int newStoreLockComplexity);
int deleteSupply(Service* service, int locationCode);
DynamicArray* listSupplies(Service* service);
DynamicArray* listSuppliesBySupplyType(Service* service, char* supplyType);
DynamicArray* listSuppliesByStoreLockComplexity(Service* service, int maximumStoreLockComplexity);
int undoService(Service* service);
int redoService(Service* service);