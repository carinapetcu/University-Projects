#include "Quiz.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "Presenter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // Quiz w;
   // w.show();

	std::ifstream fileIn("participants.txt");
	Participant currentParticipant;
	std::string pathQuestions{ "questions.txt" };
	std::string pathParticipants{ "participants.txt" };
	std::shared_ptr<Repository<Question>> question = std::make_shared<FileRepository<Question>>(pathQuestions);
	std::shared_ptr<Repository<Participant>> participant = std::make_shared<FileRepository<Participant>>(pathParticipants);
	Service service{ *question.get(), *participant.get() };
	while (fileIn >> currentParticipant)
	{
		Quiz* window = new Quiz(service, currentParticipant);
		window->setWindowTitle(QString::fromStdString(currentParticipant.getName()));
		service.addObserver(window);
		window->show();
	}
	fileIn.close();
	Presenter presenterWindow(service);
	service.addObserver(&presenterWindow);
	presenterWindow.show();
    return a.exec();
}
