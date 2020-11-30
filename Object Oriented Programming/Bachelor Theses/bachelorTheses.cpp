#include "bachelorTheses.h"
#include "editStudentsWindow.h"

bachelorTheses::bachelorTheses(Service& service, std::string name,QWidget *parent)
    : service(service), name(name), QMainWindow(parent)
{
    ui.setupUi(this);
    this->populateList();
    this->connectSingalsAndSlots();
}

void bachelorTheses::populateList()
{
    this->ui.coordinatedStudentsListWidget->clear();
    std::vector<Student> entities = this->service.getAllStudentCoordinatedByTeacher(name);
    for (auto& entity : entities)
    {
        this->ui.coordinatedStudentsListWidget->addItem(QString::fromStdString(entity.getName()));
    }
}

void bachelorTheses::update()
{
    this->populateList();
    this->filterList();
}

void bachelorTheses::connectSingalsAndSlots()
{
    QObject::connect(this->ui.searchLineEdit, &QLineEdit::textChanged, this, &bachelorTheses::filterList);
    QObject::connect(this->ui.addAsCoordinatorPushButton, &QPushButton::clicked, this, &bachelorTheses::addAsCoordinator);
    QObject::connect(this->ui.editPushButton, &QPushButton::clicked, this, &bachelorTheses::editStudent);
    QObject::connect(this->ui.listWidget, &QListWidget::itemSelectionChanged, this, &bachelorTheses::activateButton);
}

void bachelorTheses::addAsCoordinator()
{
    int selectedIndex = this->getSelectedIndex();
    std::string filterString = this->ui.searchLineEdit->text().toStdString();
    std::string studentId = this->service.filterStudentsByNameOrId(filterString)[selectedIndex].getId();
    this->service.addTeacherAsCoordinator(studentId, this->name);
    
}

void bachelorTheses::editStudent()
{
    editStudentsWindow* window = new editStudentsWindow{ this->service, this->name };
    this->service.addObserver(window);
    window->show();
}

void bachelorTheses::filterList()
{
    this->ui.listWidget->clear();
    std::string filterString = this->ui.searchLineEdit->text().toStdString();
    std::vector<Student> entities = this->service.filterStudentsByNameOrId(filterString);
    for (auto& entity : entities)
    {
        this->ui.listWidget->addItem(QString::fromStdString(entity.getId() + " - " + entity.getName() + " - " + entity.getEmail() + " - " + std::to_string(entity.getYear()) + " - " + entity.getTitle() + " - " + entity.getCoordinator()));
    }
}

int bachelorTheses::getSelectedIndex() const
{
    QModelIndexList selectedIndices = this->ui.listWidget->selectionModel()->selectedIndexes();
    if (selectedIndices.size() == 0)
    {

        return -1;
    }
    int selectedIndex = selectedIndices.at(0).row();
    return selectedIndex;
}

void bachelorTheses::activateButton()
{
    int selectedIndex = this->getSelectedIndex();
    std::string filterString = this->ui.searchLineEdit->text().toStdString();
    if (selectedIndex != -1)
    {
        if (this->service.filterStudentsByNameOrId(filterString)[selectedIndex].getCoordinator() == " ")
            this->ui.addAsCoordinatorPushButton->setEnabled(true);
        else
            this->ui.addAsCoordinatorPushButton->setEnabled(false);
    }
}
