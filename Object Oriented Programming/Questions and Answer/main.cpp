#include "QuestionAndAnswerSite.h"
#include "Search.h"
#include "Service.h"
#include "Repository.h"
#include <QtWidgets/QApplication>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	std::ifstream fileIn("users.txt");
	std::string name;
	std::vector<std::string> names;
	while (fileIn >> name)
	{
		names.push_back(name);
	}
	fileIn.close();
	std::string pathQuestions{ "questions.txt" };
	std::string pathAnswers{ "answers.txt" };
	std::shared_ptr<Repository<Question>> question = std::make_shared<FileRepository<Question>>(pathQuestions);
	std::shared_ptr<Repository<Answer>> answser = std::make_shared<FileRepository<Answer>>(pathAnswers);
	Service service{ *question.get(), *answser.get() };
	for (int i = 0; i < names.size(); i++) 
	{
		QuestionAndAnswerSite* windows = new QuestionAndAnswerSite(service, names[i]);
		windows->setWindowTitle(QString::fromStdString(names[i]));
		service.addObserver(windows);
		windows->show();
		
	}
	Search searchWindow(service);
	service.addObserver(&searchWindow);
	searchWindow.show();
    return a.exec();
}
