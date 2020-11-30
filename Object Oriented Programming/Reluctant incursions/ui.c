#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

UI* createUI(Service* service)
{
	UI* ui = (UI*)malloc(sizeof(UI));
	if (ui == NULL)
		return NULL;
	ui->service = service;
	return ui;
}

void destroyUI(UI* ui)
{
	destroyService(ui->service);
	free(ui);
}

int checkIfInteger(char* whichParameter)
{
	int index;
	for (index = 0; index < strlen(whichParameter); index++)
		if (whichParameter[index] < '0' || whichParameter[index] > '9')
			return 0;
	return 1;
}

void addSupplyUI(UI* ui, char userInput[])
{
	char* command = strtok(userInput, " ");
	char* locationCodeChar = strtok(NULL, ", ");
	char* storeType = strtok(NULL, ", ");
	char* supplyType = strtok(NULL, ", ");
	char* storeLockComplexityChar = strtok(NULL, ", ");
	// I will convert the locationCode and the storeLockComplexity integers
	int locationCode = atoi(locationCodeChar);
	int storeLockComplexity = atoi(storeLockComplexityChar);

	if (addSupply(ui->service, locationCode, storeType, supplyType, storeLockComplexity) == 0)
		printf("No!\n");
}

void listUI(UI* ui, char userInput[])
{
	int index;
	char* command = strtok(userInput, " ");
	char* whichParameter = strtok(NULL, " ");
	DynamicArray* dynamicArray;
	if (whichParameter == NULL)
		dynamicArray = listSupplies(ui->service);
	else 
	{
		int isInteger = checkIfInteger(whichParameter);
		if (isInteger == 1)
			dynamicArray = listSuppliesByStoreLockComplexity(ui->service, atoi(whichParameter));
		else
			dynamicArray = listSuppliesBySupplyType(ui->service, whichParameter);
	}
	for (index = 0; index < getSizeOfArray(dynamicArray); index++)
		printf("Location code: %i, Store type: %s, Supply type: %s, Store lock complexity: %i\n", 
			getLocationCode(getElementFromPosition(dynamicArray, index)),
			getStoreType(getElementFromPosition(dynamicArray, index)), 
			getSupplyType(getElementFromPosition(dynamicArray, index)), 
			getStoreLockComplexity(getElementFromPosition(dynamicArray, index)));
	destroyDynamicArray(dynamicArray);
}

void updateUI(UI* ui, char userInput[])
{
	char* command = strtok(userInput, " ");
	char* locationCodeChar = strtok(NULL, ", ");
	char* newStoreType = strtok(NULL, ", ");
	char* newSupplyType = strtok(NULL, ", ");
	char* newStoreLockComplexityChar = strtok(NULL, ", ");
	// I will convert the locationCode and the newStoreLockComplexity integers
	int locationCode = atoi(locationCodeChar);
	int newStoreLockComplexity = atoi(newStoreLockComplexityChar);
	updateSupply(ui->service, locationCode, newStoreType, newSupplyType, newStoreLockComplexity);
}

void deleteUI(UI* ui, char userInput[])
{
	char* command = strtok(userInput, " ");
	char* locationCodeChar = strtok(NULL, " ");
	int locationCode = atoi(locationCodeChar);
	if (deleteSupply(ui->service, locationCode) == 0)
		printf("No!\n");
}

void undoUI(UI* ui)
{
	if (undoService(ui->service) == 0)
		printf("No more actions to be undone!\n");
}

void redoUI(UI* ui)
{
	if (redoService(ui->service) == 0)
		printf("No more actions to be redone!\n");
}

void start_application(UI* ui)
{
	char userInput[100];
	char copyOfUserInput[100];
	while (1)
	{
		printf(">>");
		gets(userInput);
		strcpy(copyOfUserInput, userInput);
		if (strcmp(userInput, "exit") == 0)
			break;
		char* command = strtok(copyOfUserInput, " ");
		if (strcmp(command, "add") == 0)
			addSupplyUI(ui, userInput);
		if (strcmp(command, "list") == 0)
			listUI(ui, userInput);
		if (strcmp(command, "update") == 0)
			updateUI(ui, userInput);
		if (strcmp(command, "delete") == 0)
			deleteUI(ui, userInput);
		if (strcmp(command, "undo") == 0)
			undoUI(ui);
		if (strcmp(command, "redo") == 0)
			redoUI(ui);
	}
}