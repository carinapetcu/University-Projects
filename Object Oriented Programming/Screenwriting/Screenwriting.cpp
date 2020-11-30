#include "Screenwriting.h"
#include <qmessagebox.h>

Screenwriting::Screenwriting(Service& service, TapesTableModel* model, Writer writer,QWidget *parent)
    : service(service), model(model), writer(writer), QMainWindow(parent)
{
    ui.setupUi(this);
    this->ui.ideasTableView->setModel(model);
    this->ui.ideasTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui.ideasTableView->resizeColumnsToContents();
    this->ui.ideasTableView->resizeRowsToContents();
    if (this->writer.getExpertise() != "Senior")
        this->ui.revisePushButton->setEnabled(false);
    this->connectSignalsAndSlots();
}

void Screenwriting::update()
{
    this->model->update();
}

void Screenwriting::connectSignalsAndSlots()
{
    QObject::connect(this->ui.addPushButton, &QPushButton::clicked, this, &Screenwriting::addIdea);
    QObject::connect(this->ui.revisePushButton, &QPushButton::clicked, this, &Screenwriting::reviseIdea);
}

void Screenwriting::addIdea()
{
    std::string description = this->ui.ideaLineEdit->text().toStdString();
    if (description.empty())
    {
        QMessageBox::critical(this, "Error", "Invalid question!");
        return;
    }
    std::string actString = this->ui.actLineEdit->text().toStdString();
    if (actString.empty())
    {
        QMessageBox::critical(this, "Error", "Invalid act!");
        return;
    }
    int act = std::stoi(actString);
    try {
        this->service.addIdea(description, this->writer.getName(), act);
        
    }
    catch (RepositoryException& e)
    {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    catch (ValidationException& e)
    {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
}

void Screenwriting::reviseIdea()
{
    std::string description = this->ui.ideaLineEdit->text().toStdString();
    if (description.empty())
    {
        QMessageBox::critical(this, "Error", "Invalid question!");
        return;
    }
    std::string actString = this->ui.actLineEdit->text().toStdString();
    if (actString.empty())
    {
        QMessageBox::critical(this, "Error", "Invalid act!");
        return;
    }
    int act = std::stoi(actString);
    try {
        this->service.reviseIdea(description, this->writer.getName(), act);

    }
    catch (RepositoryException& e)
    {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
}
