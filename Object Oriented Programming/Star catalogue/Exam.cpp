#include "Exam.h"
#include <qmessagebox.h>
#include <qsortfilterproxymodel.h>
#include "AnotherWindow.h"

Exam::Exam(Service& service, Astronomer astronomer, TableModel* model, QWidget *parent)
    :service(service), astronomer(astronomer), model(model), QMainWindow(parent)
{
    ui.setupUi(this);
    this->connectSignalsAndSlots();
    this->ui.starsTableView->setModel(this->model);
    this->ui.starsTableView->hideColumn(4);
    this->ui.starsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui.starsTableView->resizeColumnsToContents();
    this->ui.starsTableView->resizeRowsToContents();
    
}

void Exam::view()
{
    AnotherWindow* viewConstellation = new AnotherWindow{ this->service, this->astronomer.getConstellation() };
    viewConstellation->show();
}

void Exam::connectSignalsAndSlots()
{
    QObject::connect(this->ui.searchLineEdit, &QLineEdit::textChanged, this, &Exam::seeFiltered);
    QObject::connect(this->ui.addPushButton, &QPushButton::clicked, this, &Exam::add);
    QObject::connect(this->ui.viewPushButton, &QPushButton::clicked, this, &Exam::view);
    QObject::connect(this->ui.showConstellationCheckBox, &QCheckBox::stateChanged, this, &Exam::showConstellation);
}

void Exam::update()
{
    this->model->update();
}

void Exam::add()
{
    std::string name = this->ui.nameLineEdit->text().toStdString();
    if (name.empty())
    {
        QMessageBox::critical(this, "Error", "Invalid name!");
        return;
    }
    int RA;
    std::string RAline = this->ui.RALineEdit->text().toStdString();
    if (RAline.empty())
        RA = 0;
    else
        RA = std::stoi(RAline);
    int Dec;
    std::string DecLine = this->ui.DacLineEdit->text().toStdString();
    if (DecLine.empty())
        Dec = 0;
    else
        Dec = std::stoi(DecLine);
    int diameter;
    std::string diameterLine = this->ui.diameterLineEdit->text().toStdString();
    if (diameterLine.empty())
        diameter = 0;
    else
        diameter = std::stoi(diameterLine);
    if(diameter <= 0)
    {
        QMessageBox::critical(this, "Error", "Invalid diameter!");
        return;
    }
    try {
        this->service.addStar(name, this->astronomer.getConstellation(), RA, Dec, diameter);

    }
    catch (RepositoryException& e)
    {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
}

void Exam::showConstellation()
{
    if (this->ui.showConstellationCheckBox->isChecked())
    {
        QSortFilterProxyModel* proxyModel =
            new QSortFilterProxyModel{};
        proxyModel->setSourceModel(this->model);
        this->ui.starsTableView->setSortingEnabled(true);
        proxyModel->setFilterRegExp(QRegExp(QString::fromStdString(this->astronomer.getConstellation()), Qt::CaseInsensitive, QRegExp::FixedString));
        proxyModel->setFilterKeyColumn(4);

        this->ui.starsTableView->setModel(proxyModel);
        this->ui.starsTableView->hideColumn(4);
        this->ui.starsTableView->resizeColumnsToContents();
    }
    else
    {
        this->ui.starsTableView->setModel(this->model);
        this->ui.starsTableView->hideColumn(4);
        this->ui.starsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        this->ui.starsTableView->resizeColumnsToContents();
        this->ui.starsTableView->resizeRowsToContents();
    }
}

void Exam::seeFiltered()
{
    this->ui.filterListWidget->clear();
    std::string filterString = this->ui.searchLineEdit->text().toStdString();
    std::vector<Star> entities = this->service.getFiltered(filterString);
    for (auto& entity : entities)
    {
        this->ui.filterListWidget->addItem(QString::fromStdString(entity.getName() + " - " + entity.getConstellation() + " - " + std::to_string(entity.getRA()) + " - " + std::to_string(entity.getDec()) + " - " + std::to_string(entity.getDiameter())));
    }
}
