#include "Tests.h"
#include "Repository.h"
#include "Domain.h"
#include "Service.h"
#include <assert.h>

void testFileRepositoryAddWithFiles_validInput_addsEntity()
{
	std::string filePath{ "test.txt" };
	FileRepository<Star> repository{ filePath };
	try
	{
		repository.add(Star{"askd","sada",10,10,10});
		assert(true);
	}
	catch (RepositoryException& exception)
	{
	}
	assert(repository.getSizeOfRepository() == 1);
	std::ofstream fileOut(filePath, std::ios::trunc);
	fileOut.close();
}

void testFileRepositoryAdd_invalidElement_doesNotAddElement()
{
	std::string filePath{ "test.txt" };
	FileRepository<Star> repository{ filePath };
	repository.add(Star{"123","askd",10,10,1});
	try
	{
		repository.add(Star{ "123","askd",10,10,1 });
	}
	catch (RepositoryException& exception)
	{
		assert(true);
	}
	assert(repository.getSizeOfRepository() == 1);
	std::ofstream fileOut(filePath, std::ios::trunc);
	fileOut.close();
}

void testAddElementService_validInput_addsElementToRepository()
{
	std::string filePath{ "test.txt" };
	FileRepository<Star> repository{ filePath };
	Service service{ repository };
	service.addStar("F1423", "level 3 food court", 1, 13, 2028);
	assert(repository.getSizeOfRepository() == 1);
	std::ofstream fileOut(filePath, std::ios::trunc);
	fileOut.close();
}


void testAll()
{
	testFileRepositoryAddWithFiles_validInput_addsEntity();
	testFileRepositoryAdd_invalidElement_doesNotAddElement();
	testAddElementService_validInput_addsElementToRepository();
}
