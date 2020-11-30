#pragma once

typedef struct{
	int locationCode;
	char* storeType;
	char* supplyType;
	int storeLockComplexity;
}Supply;

Supply* createSupply(int locationCode, char* storeType, char* supplyType, int storeLockComplexity);
void destroySupply(Supply* supply);

int getLocationCode(Supply* supply);
char* getStoreType(Supply* supply);
char* getSupplyType(Supply* supply);
int getStoreLockComplexity(Supply* supply);

void setStoreType(Supply* supply, char* storeType);
void setSupplyType(Supply* supply, char* supplyType);
void setStoreLockComplexity(Supply* supply, int storeLockComplexity);
