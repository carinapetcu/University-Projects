#include "Service.h"
#include <iostream>

std::vector<Domain> Service::getAllElements()
{
	return this->repository.getAll();
	
}

float Service::getUnpaidBillsTotal(std::string company)
{
	std::vector<Domain> allBills;
	float total = 0;
	for (auto& bill : allBills)
		if (bill.getCompanyName() == company && !bill.getIsPaid())
			total += bill.getSum();
	return total;
}
