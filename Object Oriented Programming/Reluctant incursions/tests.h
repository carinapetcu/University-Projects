#include "domain.h"
#include "dynamicArray.h"
#include "repository.h"
#include "service.h"
#include "undoRedo.h"
#include "stack.h"

void testDomainCreateSupply();
void testDomainGetLocationCode();
void testDomainGetSupplyType();
void testDomainGetStoreType();
void testDomainGetStoreLockComplexity();
void testDomainSetSupplyType();
void testDomainSetStoreType();
void testDomainSetStoreLockComplexity();

void testUndoRedoCreate();
void testUndoRedoGetAction();
void testUndoRedoGetSupply();
void testUndoRedoSetAction();
void testUndoRedoSetSupply();

void testDynamicArrayCreate();
void testDynamicArrayAdd();
void testDynamicArraySearch();
void testDynamicArraySearch();
void testDynamicArrayUpdate();
void testDynamicArraySize();
void testDynamicArrayGetElement();
void testDynamicArraySwapElements();

void testStackCreate();
void testStackResize();
void testStackGetSize();
void testStackPush();
void testStackPop();

void testRepositoryCreate();
void testRepositoryGetSize();
void testRepositoryAdd();
void testRepositoryDelete();
void testRepositoryUpdate();
void testRepositoryGetAll();

void testServiceCreate();
void testServiceAdd();
void testServiceUpdate();
void testServiceDelete();
void testServiceList();
void testServiceListBySupplyType();
void testListSuppliesByStoreLockComplexity();
void testServiceUndo();
void testServiceRedo();

void do_all_tests();