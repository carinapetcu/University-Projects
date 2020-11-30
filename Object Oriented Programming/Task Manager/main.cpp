#include "TaskManagerButMakeItWithGUI.h"
#include <QtWidgets/QApplication>
#include "Repository.h"
#include "Service.h"
#include "Tape.h"
#include <memory>
#include <string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::string path{ "input.txt" };
    std::unique_ptr<Repository> repository = std::make_unique<FileRepository>(path);
    Service service{ *repository.get() };
    TaskManagerButMakeItWithGUI w{service};
    w.show();
    return a.exec();
}
