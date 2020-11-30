#pragma once
#include "service.h"
#include "dynamicArray.h"
#include "domain.h"

typedef struct {
	Service* service;
}UI;

UI* createUI(Service* service);
void destroyUI(UI* ui);

void start_application(UI* ui);
void addSupplyUI(UI* ui, char userInput[]);
void listUI(UI* ui, char userInput[]);
void updateUI(UI* ui, char userInput[]);
void deleteUI(UI* ui, char userInput[]);
void undoUI(UI* ui);
void redoUI(UI* ui);
int checkIfInteger(char* whichParameter);