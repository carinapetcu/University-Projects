#include "domain.h"
#include <string.h>
#include <stdlib.h>

Supply* createSupply(int locationCode, char* storeType, char* supplyType, int storeLockComplexity)
{
	Supply* supply = (Supply*)malloc(sizeof(Supply));
	if (supply == NULL)
		return NULL;

	supply->locationCode = locationCode;

	supply->storeType = NULL;
	supply->supplyType = NULL;

	setStoreType(supply, storeType);
	setSupplyType(supply, supplyType);
	setStoreLockComplexity(supply, storeLockComplexity);

	return supply;
}

void destroySupply(Supply* supply)
{
	if (supply == NULL)
		return;
	free(supply->supplyType);
	free(supply->storeType);
	free(supply);
}

int getLocationCode(Supply* supply)
{
	if (supply == NULL)
		return -1;
	return supply->locationCode;
}

char* getStoreType(Supply* supply)
{
	if (supply == NULL)
		return NULL;
	return supply->storeType;
}

char* getSupplyType(Supply* supply)
{
	if (supply == NULL)
		return NULL;
	return supply->supplyType;
}

int getStoreLockComplexity(Supply* supply)
{
	if (supply == NULL)
		return NULL;
	return supply->storeLockComplexity;
}



void setStoreType(Supply* supply, char* storeType)
{
	if (supply->storeType != NULL)
	{
		free(supply->storeType);
		supply->storeType = NULL;
	}
	if(supply->storeType == NULL)
	supply->storeType = (char*)malloc(sizeof(char) * (strlen(storeType) + 1));
	strcpy(supply->storeType, storeType);
	
}

void setSupplyType(Supply* supply, char* supplyType)
{
	if (supply->supplyType != NULL)
	{
		free(supply->supplyType);
		supply->supplyType = NULL;
	}

	supply->supplyType = (char*)malloc(sizeof(char) * (strlen(supplyType) + 1));
	strcpy(supply->supplyType, supplyType);
}

void setStoreLockComplexity(Supply* supply, int newStoreLockComplexity)
{
	if (supply == NULL)
		return;
	supply->storeLockComplexity = newStoreLockComplexity;
}
