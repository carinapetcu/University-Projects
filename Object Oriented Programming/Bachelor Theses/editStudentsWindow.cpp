#include "editStudentsWindow.h"

editStudentsWindow::editStudentsWindow(Service& service, std::string name, QWidget *parent)
	: service(service), name(name), QWidget(parent)
{
	ui.setupUi(this);
	this->populateList();
    this->connectSignalsAndSlots();
}

editStudentsWindow::~editStudentsWindow()
{
}

void editStudentsWindow::populateList()
{
    this->ui.listWidget->clear();
    std::vector<Student> entities = this->service.getAllStudentCoordinatedByTeacher(this->name);
    for (auto& entity : entities)
    {
        this->ui.listWidget->addItem(QString::fromStdString(entity.getId() + " - " + entity.getName() + " - " + entity.getEmail() + " - " + std::to_string(entity.getYear()) + " - " + entity.getTitle() + " - " + entity.getCoordinator()));
    }
}

void editStudentsWindow::connectSignalsAndSlots()
{
   QObject::connect(this->ui.savePushButton, &QPushButton::clicked, this, &editStudentsWindow::editStudent);
}

void editStudentsWindow::update()
{
    this->populateList();
}

void editStudentsWindow::editStudent()
{
    std::string newEmail = this->ui.emailLineEdit->text().toStdString();
    std::string newTitle = this->ui.titleLineEdit->text().toStdString();
    int selectedIndex = this->getSelectedIndex();
    if (selectedIndex != -1) {
        if (!newEmail.empty())
            this->service.updateEmail(this->service.getAllStudentCoordinatedByTeacher(this->name)[selectedIndex].getId(), newEmail);
        if (!newTitle.empty())
            this->service.updateThesisTitle(this->service.getAllStudentCoordinatedByTeacher(this->name)[selectedIndex].getId(), newTitle);
    }
}

int editStudentsWindow::getSelectedIndex() const
{
    QModelIndexList selectedIndices = this->ui.listWidget->selectionModel()->selectedIndexes();
    if (selectedIndices.size() == 0)
    {
        return -1;
    }
    int selectedIndex = selectedIndices.at(0).row();
    return selectedIndex;
}
