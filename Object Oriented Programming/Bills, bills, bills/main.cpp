#include "DollarsDollarsDollars.h"
#include <QtWidgets/QApplication>
#include <memory>
#include "Repository.h"
#include "Service.h"
#include "Domain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::string path{ "input.txt" };
    std::unique_ptr<Repository<Domain>> repository = std::make_unique<FileRepository<Domain>>(path);
    Service service{ *repository.get() };
    DollarsDollarsDollars w{service};
    w.show();
    return a.exec();
}
