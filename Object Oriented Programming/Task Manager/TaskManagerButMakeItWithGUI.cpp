#include "TaskManagerButMakeItWithGUI.h"

TaskManagerButMakeItWithGUI::TaskManagerButMakeItWithGUI(Service& service, QWidget *parent)
    : QMainWindow(parent), service(service)
{
    ui.setupUi(this);
    this->populateList();
    this->connectSignalsAndSlots();

}

void TaskManagerButMakeItWithGUI::populateList()
{
    this->ui.priorityListWidget->clear();
    this->ui.priorityListWidget->setSortingEnabled(true);
    std::vector<Task> allTapes = this->service.getAllElements();
    for (auto tape : allTapes)
    {
        this->ui.priorityListWidget->addItem(QString::fromStdString(std::to_string(tape.getPriority()) + "|" + std::to_string(tape.getDuration()) + "|" + tape.getDescription()));
    }
    this->ui.priorityListWidget->sortItems();
}

void TaskManagerButMakeItWithGUI::connectSignalsAndSlots()
{
    QObject::connect(this->ui.durationPushButton, &QPushButton::clicked, this, &TaskManagerButMakeItWithGUI::getDurationByPriority);
}

void TaskManagerButMakeItWithGUI::getDurationByPriority()
{
    int priority = stoi(this->ui.priorityLineEdit->text().toStdString());
    int duration = 0;
    std::vector<Task> allTapes = this->service.getAllElements();
    for (auto tape : allTapes)
    {
        if (tape.getPriority() == priority)
            duration += tape.getDuration();
    }
    this->ui.durationLineEdit->setText(QString::fromStdString(std::to_string(duration)));
}
