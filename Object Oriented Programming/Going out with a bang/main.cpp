#include "Goingoutwithabang.h"
#include "myListTable.h"
#include <QtWidgets/QApplication>
#include "Repository.h"
#include "TapesTableModel.h"
#include "TapesListModel.h"
#include <memory>
#include "Tape.h"
#include <string>
#include "Service.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	std::ifstream fileIn("configurationFile.txt");
	std::string currentLine;
	std::getline(fileIn, currentLine); // we read the first line to see whether we have an inmemory or file repository
	std::shared_ptr<Repository<Tape>> repository;
	std::shared_ptr<Repository<Tape>> watchList;
	std::size_t found = currentLine.find("inmemory");
	if (found != std::string::npos) // the repository is inmemory and we read the next lines correspondingly
	{
		repository = std::make_shared<Repository<Tape>>();
	}
	else // the repository is a file one
	{
		std::getline(fileIn, currentLine); // we read the first line to see whether we have an inmemory or file repository
		std::size_t found = currentLine.find("=");
		currentLine.erase(0, found + 1);
		repository = std::make_shared<FileRepository<Tape>>(currentLine);
	}

	std::getline(fileIn, currentLine); // we read the first line to see whether we have an inmemory or file repository
	found = currentLine.find("inmemory");
	if (found != std::string::npos) // the repository is inmemory and we read the next lines correspondingly
	{
		watchList = std::make_shared<Repository<Tape>>();
	}
	else // the repository is a file one
	{
		std::getline(fileIn, currentLine);
		found = currentLine.find("=");
		currentLine.erase(0, found + 1);
		std::string copyOfPath{ currentLine };
		size_t positionOfDot = copyOfPath.find_last_of('.');
		copyOfPath.erase(0, positionOfDot + 1);
		if (copyOfPath.size() == 3)
		{
			watchList = std::make_shared<CSVWatchList<Tape>>(currentLine);
		}
		else
			if (copyOfPath.size() == 4)
			{
				watchList = std::make_shared<HTMLWatchList<Tape>>(currentLine);
			}
	}

	Service service{ *repository.get(), *watchList.get() };
	Goingoutwithabang gui{ service };
	service.addObserver(&gui);
	gui.show();
	return a.exec();
}
