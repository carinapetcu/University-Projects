#include "tests.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

void testDomainCreateSupply()
{
	Supply* newSupply = createSupply(123, "aaa", "aba", 456);
	assert(newSupply->locationCode == 123);
	assert(strcmp(newSupply->supplyType, "aba") == 0);
	assert(strcmp(newSupply->storeType, "aaa") == 0);
	assert(newSupply->storeLockComplexity == 456);
	destroySupply(newSupply);
}

void testDomainGetLocationCode()
{
	Supply* newSupply = createSupply(123, "aaa", "aba", 456);
	int locationCode = getLocationCode(newSupply);
	assert(locationCode == 123);
	destroySupply(newSupply);
}

void testDomainGetSupplyType()
{
	Supply* newSupply = createSupply(123, "aaa", "aba", 456);
	char* supplyType;
	supplyType = getSupplyType(newSupply);
	assert(strcmp(supplyType, "aba") == 0);
	destroySupply(newSupply);
}

void testDomainGetStoreType()
{
	Supply* newSupply = createSupply(123, "aaa", "aba", 456);
	char* storeType;
	storeType = getStoreType(newSupply);
	assert(strcmp(storeType, "aaa") == 0);
	destroySupply(newSupply);
}

void testDomainGetStoreLockComplexity()
{
	Supply* newSupply = createSupply(123, "aaa", "aba", 456);
	int storeLockComplexity = getStoreLockComplexity(newSupply);
	assert(storeLockComplexity == 456);
	destroySupply(newSupply);
}

void testDomainSetSupplyType()
{
	Supply* newSupply = createSupply(123, "aaa", "aba", 456);
	setSupplyType(newSupply, "edf");
	assert(strcmp(getSupplyType(newSupply), "edf") == 0);
	destroySupply(newSupply);
}

void testDomainSetStoreType()
{
	Supply* newSupply = createSupply(123, "aaa", "aba", 456);
	setStoreType(newSupply, "bab");
	assert(strcmp(getStoreType(newSupply), "bab") == 0);
	destroySupply(newSupply);
}

void testDomainSetStoreLockComplexity()
{
	Supply* newSupply = createSupply(123, "aaa", "aba", 456);
	setStoreLockComplexity(newSupply, 300);
	assert(getStoreLockComplexity(newSupply) == 300);
	destroySupply(newSupply);
}

void testUndoRedoCreate()
{
	Supply* supply = createSupply(123, "aaa", "aba", 40);
	UndoRedo* undo = createUndoRedo("remove", supply);
	assert(strcmp(undo->action, "remove") == 0);
	destroyUndoRedo(undo);
}

void testUndoRedoGetAction()
{
	Supply* supply = createSupply(123, "aaa", "aba", 40);
	UndoRedo* undo = createUndoRedo("remove", supply);
	assert(strcmp(getAction(undo), "remove") == 0);
	destroyUndoRedo(undo);
}

void testUndoRedoGetSupply()
{
	Supply* supply = createSupply(123, "aaa", "aba", 40);
	UndoRedo* undo = createUndoRedo("remove", supply);
	assert(getLocationCode(getSupply(undo)) == 123);
	destroyUndoRedo(undo);
}

void testUndoRedoSetAction()
{
	Supply* supply = createSupply(123, "aaa", "aba", 40);
	UndoRedo* undo = createUndoRedo("remove", supply);
	setAction(undo, "add");
	assert(strcmp(getAction(undo), "add") == 0);
	destroyUndoRedo(undo);
}

void testUndoRedoSetSupply()
{
	Supply* supply = createSupply(123, "aaa", "aba", 40);
	Supply* newSupply = createSupply(1, "sagg", "fd", 30);
	UndoRedo* undo = createUndoRedo("remove", supply);
	setSupply(undo, newSupply);
	assert(getLocationCode(getSupply(undo)) == 1);
	destroyUndoRedo(undo);
}

void testDynamicArrayCreate()
{
	DynamicArray* newDynamicArray = createDynamicArray(10);
	assert(newDynamicArray->capacity == 10);
	assert(newDynamicArray->length == 0);
	destroyDynamicArray(newDynamicArray);
}

void testDynamicArrayResize()
{
	DynamicArray* newDynamicArray = createDynamicArray(10);
	resizeDynamicArray(newDynamicArray);
	assert(newDynamicArray->capacity == 20);
	destroyDynamicArray(newDynamicArray);
}

void testDynamicArrayAdd()
{
	DynamicArray* newDynamicArray = createDynamicArray(10);
	Supply* supply = createSupply(123, "aaa", "aba", 456);
	addElement(newDynamicArray, supply);
	assert(newDynamicArray->length == 1);
	assert(getLocationCode(newDynamicArray->elements[0]) == getLocationCode(supply));
	destroyDynamicArray(newDynamicArray);
}

void testDynamicArraySearch()
{
	DynamicArray* newDynamicArray = createDynamicArray(10);
	Supply* supply = createSupply(123, "aaa", "aba", 456);
	addElement(newDynamicArray, supply);
	int index = searchElement(newDynamicArray, supply);
	assert(index == 0);
	destroyDynamicArray(newDynamicArray);
}

void testDynamicArrayDelete()
{
	DynamicArray* newDynamicArray = createDynamicArray(10);
	Supply* supply1 = createSupply(123, "aaa", "aba", 456);
	Supply* supply2 = createSupply(567, "aaa", "aba", 456);
	addElement(newDynamicArray, supply1);
	addElement(newDynamicArray, supply2);
	deleteElement(newDynamicArray, 0, supply1);
	assert(newDynamicArray->length == 1);
	destroySupply(supply1);
	destroyDynamicArray(newDynamicArray);
}

void testDynamicArrayUpdate()
{
	DynamicArray* newDynamicArray = createDynamicArray(10);
	Supply* supply = createSupply(123, "aaa", "aba", 456);
	addElement(newDynamicArray, supply);
	Supply* newSupply = createSupply(145, "dfc", "eld", 20);
	updateElement(newDynamicArray, newSupply, 0);
	assert(getLocationCode(newDynamicArray->elements[0]) == 145);
	assert(strcmp(getStoreType(newDynamicArray->elements[0]), "dfc") == 0);
	assert(strcmp(getSupplyType(newDynamicArray->elements[0]), "eld") == 0);
	assert(getStoreLockComplexity(newDynamicArray->elements[0]) == 20);
	destroyDynamicArray(newDynamicArray);
}

void testDynamicArraySize()
{
	DynamicArray* newDynamicArray = createDynamicArray(10);
	Supply* supply = createSupply(123, "aaa", "aba", 456);
	addElement(newDynamicArray, supply);
	assert(getSizeOfArray(newDynamicArray) == 1);
	destroyDynamicArray(newDynamicArray);
}

void testDynamicArrayGetElement()
{
	DynamicArray* newDynamicArray = createDynamicArray(10);
	Supply* supply = createSupply(123, "aaa", "aba", 456);
	addElement(newDynamicArray, supply);
	Supply* element = getElementFromPosition(newDynamicArray, 0);
	assert(getLocationCode(element) == getLocationCode(supply));
	assert(strcmp(getStoreType(element), getStoreType(supply)) == 0);
	assert(strcmp(getSupplyType(element), getSupplyType(supply)) == 0);
	assert(getStoreLockComplexity(element) == getStoreLockComplexity(supply));
	destroyDynamicArray(newDynamicArray);
}

void testDynamicArraySwapElements()
{
	DynamicArray* newDynamicArray = createDynamicArray(10);
	Supply* supply1 = createSupply(123, "aaa", "aba", 456);
	Supply* supply2 = createSupply(567, "aaa", "aba", 456);
	addElement(newDynamicArray, supply1);
	addElement(newDynamicArray, supply2);
	swapElements(newDynamicArray, 0, 1);
	assert(getLocationCode(getElementFromPosition(newDynamicArray, 0)) == 567);
	assert(getLocationCode(getElementFromPosition(newDynamicArray, 1)) == 123);
	destroyDynamicArray(newDynamicArray);
}

void testStackCreate()
{
	Stack* stack = createStack(10);
	assert(stack->capacity == 10);
	destroyStack(stack);
}

void testStackResize()
{
	Stack* stack = createStack(10);
	resize(stack);
	assert(stack->capacity == 20);
	destroyStack(stack);
}

void testStackGetSize()
{
	Stack* stack = createStack(10);
	assert(getSizeOfStack(stack) == 0);
	destroyStack(stack);
}

void testStackPush()
{
	Stack* stack = createStack(10);
	Supply* supply = createSupply(123, "aaa", "aba", 456);
	UndoRedo* undo = createUndoRedo("remove", supply);
	push(stack, undo);
	assert(getLocationCode(getSupply(stack->elements[0])) == 123);
	destroyStack(stack);
}

void testStackPop()
{
	Stack* stack = createStack(10);
	Supply* supply = createSupply(123, "aaa", "aba", 456);
	UndoRedo* undo = createUndoRedo("remove", supply);
	push(stack, undo);
	UndoRedo* lastElement = pop(stack);
	assert(getSizeOfStack(stack) == 0);
	assert(getLocationCode(getSupply(lastElement)) == 123);
	destroyUndoRedo(undo);
	destroyStack(stack);
}


void testRepositoryCreate()
{
	Repository* repository = createRepository();
	assert(getSizeOfArray(repository->dynamicArray) == 0);
	destroyRepository(repository);
}

void testRepositoryGetSize()
{
	Repository* repository = createRepository();
	assert(getSize(repository) == 0);
	destroyRepository(repository);
}

void testRepositoryAdd()
{
	Repository* repository = createRepository();
	Supply* supply = createSupply(123, "aaa", "aba", 456);
	int isAdded = add(repository, supply);
	assert(getSizeOfArray(repository->dynamicArray) == 1);
	destroyRepository(repository);
}

void testRepositoryDelete()
{
	Repository* repository = createRepository();
	Supply* supply = createSupply(123, "aaa", "aba", 456);
	int isAdded = add(repository, supply);
	int isDeleted = delete(repository, supply);
	assert(getSizeOfArray(repository->dynamicArray) == 0);
	destroyRepository(repository);
}

void testRepositoryUpdate()
{
	Repository* repository = createRepository();
	Supply* supply = createSupply(123, "aaa", "aba", 456);
	int isAdded = add(repository, supply);
	assert(getSizeOfArray(repository->dynamicArray) == 1);
	Supply* newSupply = createSupply(123, "asd", "edf", 40);
	update(repository, newSupply);
	assert(getSizeOfArray(repository->dynamicArray) == 1);
	assert(strcmp(getStoreType(repository->dynamicArray->elements[0]), "asd") == 0);
	destroyRepository(repository);
}

void testRepositoryGetAll()
{
	Repository* repository = createRepository();
	Supply* supply1 = createSupply(123, "aaa", "aba", 456);
	Supply* supply2 = createSupply(456, "asd", "edf", 40);
	int isAdded = add(repository, supply1);
	isAdded = add(repository, supply2);
	DynamicArray* allElements = getAllElements(repository);
	assert(getSizeOfArray(allElements) == 2);
	destroyDynamicArray(allElements);
	destroyRepository(repository);
}

void testServiceCreate()
{
	Repository* repository = createRepository();
	Stack* undo = createStack(10);
	Stack* redo = createStack(10);
	Service* service = createService(repository, undo, redo);
	assert(getSize(service->repository) == 0);
	destroyService(service);
}

void testServiceAdd()
{
	Repository* repository = createRepository();
	Stack* undo = createStack(10);
	Stack* redo = createStack(10);
	Service* service = createService(repository, undo, redo);
	int wasAdded = addSupply(service, 123, "ads", "dhb", 10);
	assert(getSize(service->repository) == 1);
	DynamicArray* dynamicArray = getAllElements(service->repository);
	assert(getLocationCode(getElementFromPosition(dynamicArray, 0)) == 123);
	assert(strcmp(getStoreType(getElementFromPosition(dynamicArray, 0)), "ads") == 0);
	assert(strcmp(getSupplyType(getElementFromPosition(dynamicArray, 0)), "dhb") == 0);
	assert(getStoreLockComplexity(getElementFromPosition(dynamicArray, 0)) == 10);
	assert(getSizeOfStack(service->undo) == 1);
	assert(getSizeOfStack(service->redo) == 0);
	destroyDynamicArray(dynamicArray);
	destroyService(service);
}

void testServiceUpdate()
{
	Repository* repository = createRepository();
	Stack* undo = createStack(10);
	Stack* redo = createStack(10);
	Service* service = createService(repository, undo, redo);
	int wasAdded = addSupply(service, 123, "ads", "dhb", 10);
	updateSupply(service, 123, "fgh", "lal", 13);
	DynamicArray* dynamicArray = getAllElements(service->repository);
	assert(getLocationCode(getElementFromPosition(dynamicArray, 0)) == 123);
	assert(strcmp(getStoreType(getElementFromPosition(dynamicArray, 0)), "fgh") == 0);
	assert(strcmp(getSupplyType(getElementFromPosition(dynamicArray, 0)), "lal") == 0);
	assert(getStoreLockComplexity(getElementFromPosition(dynamicArray, 0)) == 13);
	assert(getSizeOfStack(service->undo) == 2);
	assert(getSizeOfStack(service->redo) == 0);
	destroyDynamicArray(dynamicArray);
	destroyService(service);
}

void testServiceDelete()
{
	Repository* repository = createRepository();
	Stack* undo = createStack(10);
	Stack* redo = createStack(10);
	Service* service = createService(repository, undo, redo);
	int wasAdded = addSupply(service, 123, "ads", "dhb", 10);
	int wasDeleted = deleteSupply(service, 123);
	assert(getSize(service->repository) == 0);
	assert(getSizeOfStack(service->undo) == 2);
	destroyService(service);
}

void testServiceList()
{

	Repository* repository = createRepository();
	Stack* undo = createStack(10);
	Stack* redo = createStack(10);
	Service* service = createService(repository, undo, redo);
	int wasAdded = addSupply(service, 123, "ads", "dhb", 10);
	wasAdded = addSupply(service, 456, "aas", "asb", 40);
	DynamicArray* dynamicArray = listSupplies(service);
	assert(getSizeOfArray(dynamicArray) == 2);
	destroyDynamicArray(dynamicArray);
	destroyService(service);
}

void testServiceListBySupplyType()
{
	Repository* repository = createRepository();
	Stack* undo = createStack(10);
	Stack* redo = createStack(10);
	Service* service = createService(repository, undo, redo);
	int wasAdded = addSupply(service, 123, "ads", "dhb", 10);
	wasAdded = addSupply(service, 456, "aas", "asb", 40);
	DynamicArray* dynamicArray = listSuppliesBySupplyType(service, "asb");
	assert(getSizeOfArray(dynamicArray) == 1);
	assert(getLocationCode(getElementFromPosition(dynamicArray, 0)) == 456);
	assert(strcmp(getStoreType(getElementFromPosition(dynamicArray, 0)), "aas") == 0);
	assert(strcmp(getSupplyType(getElementFromPosition(dynamicArray, 0)), "asb") == 0);
	assert(getStoreLockComplexity(getElementFromPosition(dynamicArray, 0)) == 40);
	destroyDynamicArray(dynamicArray);
	destroyService(service);
}

void testListSuppliesByStoreLockComplexity()
{
	Repository* repository = createRepository();
	Stack* undo = createStack(10);
	Stack* redo = createStack(10);
	Service* service = createService(repository, undo, redo);
	int wasAdded = addSupply(service, 123, "bbbb", "dhb", 10);
	wasAdded = addSupply(service, 456, "aas", "asb", 40);
	DynamicArray* dynamicArray = listSuppliesByStoreLockComplexity(service, 50);
	assert(getSizeOfArray(dynamicArray) == 2);
	assert(getStoreLockComplexity(getElementFromPosition(dynamicArray, 0)) == 40);
	assert(getStoreLockComplexity(getElementFromPosition(dynamicArray, 1)) == 10);
	destroyDynamicArray(dynamicArray);
	destroyService(service);
}

void testServiceUndo()
{
	Repository* repository = createRepository();
	Stack* undo = createStack(10);
	Stack* redo = createStack(10);
	Service* service = createService(repository, undo, redo);
	int wasAdded = addSupply(service, 999, "bbbb", "dhb", 10);
	int wasDeleted = deleteSupply(service, 999);
	int wasUndone = undoService(service);
	assert(getSizeOfStack(service->undo) == 1);
	assert(getSizeOfStack(service->redo) == 1);
	assert(getSize(service->repository) == 1);
	destroyService(service);
}

void testServiceRedo()
{
	Repository* repository = createRepository();
	Stack* undo = createStack(10);
	Stack* redo = createStack(10);
	Service* service = createService(repository, undo, redo);
	int wasAdded = addSupply(service, 999, "bbbb", "dhb", 10);
	wasAdded = addSupply(service, 10, "aaa", "sadh", 5);
	int wasDeleted = deleteSupply(service, 999);
	int wasUndone = undoService(service);
	int wasRedid = redoService(service);
	wasUndone = undoService(service);
	assert(getSizeOfStack(service->undo) == 2);
	TElemUndoRedo result = pop(service->redo);
	assert(getSizeOfStack(service->redo) == 0);
	destroyUndoRedo(result);
	destroyService(service);
}


void do_all_tests()
{
	testDomainCreateSupply();
	testDomainGetLocationCode();
	testDomainGetSupplyType();
	testDomainGetStoreType();
	testDomainGetStoreLockComplexity();
	testDomainSetSupplyType();
	testDomainSetStoreType();
	testDomainSetStoreLockComplexity();

	testUndoRedoCreate();
	testUndoRedoGetAction();
	testUndoRedoGetSupply();
	testUndoRedoSetAction();
	testUndoRedoSetSupply();

	testDynamicArrayCreate();
	testDynamicArrayResize();
	testDynamicArrayAdd();
	testDynamicArraySearch();
	testDynamicArrayDelete();
	testDynamicArrayUpdate();
	testDynamicArraySize();
	testDynamicArrayGetElement();
	testDynamicArraySwapElements();

	testStackCreate();
	testStackGetSize();
	testStackResize();
	testStackPush();
	testStackPop();

	testRepositoryCreate();
	testRepositoryGetSize();
	testRepositoryAdd();
	testRepositoryDelete();
	testRepositoryUpdate();
	testRepositoryGetAll();

	testServiceCreate();
	testServiceAdd();
	testServiceUpdate();
	testServiceDelete();
	testServiceList();
	testServiceListBySupplyType();
	testListSuppliesByStoreLockComplexity();
	testServiceUndo();
	testServiceRedo();
}