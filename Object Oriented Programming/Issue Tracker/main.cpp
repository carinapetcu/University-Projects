#include "IssueTracker.h"
#include <QtWidgets/QApplication>
#include "Domain.h"
#include "Repository.h"
#include "Service.h"
#include "Observer.h"
#include <memory>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	std::string usersFile("users.txt");
	std::string issuesFile("issues.txt");
	std::shared_ptr<Repository<User>> userRepository = std::make_shared<FileRepository<User>>(usersFile);
	std::shared_ptr<Repository<Issue>> issueRepository = std::make_shared<FileRepository<Issue>>(issuesFile);
	Service service{ *issueRepository.get() };
	for (auto user : userRepository->getAll())
	{
		IssueTracker* windows = new IssueTracker(service, user);
		windows->setWindowTitle(QString::fromStdString(user.getName() + " - " + user.getType()));
		service.addObserver(windows);
		windows->show();
	}
    return a.exec();
}
