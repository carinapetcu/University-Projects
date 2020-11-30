#include "Goingoutwithabang.h"
#include <qmessagebox.h>
#include <QShortcut>


Goingoutwithabang::Goingoutwithabang( Service& service, QWidget *parent)
	:service(service), QMainWindow(parent), position{ 0 }
{
    ui.setupUi(this);
	this->createShortcuts();
	this->populateList();
	this->connectSignalsAndSlots();
	TapesTableModel* watchListTableModel = new TapesTableModel{ this->service.getWatchList() };
	this->table = new myListTable{ watchListTableModel };
}

void Goingoutwithabang::update()
{
	this->populateList();
}

void Goingoutwithabang::populateList()
{
	this->ui.tapesModeAListWidget->clear();
	this->ui.tapesModeBListWidget->clear();

	std::vector<Tape> allTapes = this->service.getAllElements();
	for (auto tape : allTapes)
	{
		this->ui.tapesModeAListWidget->addItem(QString::fromStdString(tape.getTitle() + "-" + tape.getSection()));
		std::string date{ "" };
		date += std::to_string(tape.getDate().getMonth()) + "-" + std::to_string(tape.getDate().getDay()) + "-" + std::to_string(tape.getDate().getYear());
		this->ui.tapesModeBListWidget->addItem(QString::fromStdString(tape.getTitle() + ", " + tape.getSection() + ", " + date + ", " + std::to_string(tape.getAccessCount())
			+ ", " + tape.getFootagePreview()));
	}
}

void Goingoutwithabang::connectSignalsAndSlots()
{
	QObject::connect(this->ui.tapesModeAListWidget, &QListWidget::itemSelectionChanged, [this]() {
		int selectedIndex = this->getSelectedIndexModeA();

		if (selectedIndex < 0)
			return;

		Tape tape = this->service.getAllElements()[selectedIndex];
		this->ui.titleLineEdit->setText(QString::fromStdString(tape.getTitle()));
		this->ui.sectionLineEdit->setText(QString::fromStdString(tape.getSection()));
		this->ui.dateLineEdit->setText(QString::fromStdString(std::to_string(tape.getDate().getMonth())
			+ "-" + std::to_string(tape.getDate().getDay()) + "-" + std::to_string(tape.getDate().getYear())));
		this->ui.accessCountLineEdit->setText(QString::fromStdString(std::to_string(tape.getAccessCount())));
		this->ui.footagePreviewLineEdit->setText(QString::fromStdString(tape.getFootagePreview()));
		});
	QObject::connect(this->shortcutUndoModeA, &QShortcut::activated, this, &Goingoutwithabang::undoModeA);
	QObject::connect(this->shortcutRedoModeA, &QShortcut::activated, this, &Goingoutwithabang::redoModeA);
	QObject::connect(this->shortcutUndoModeB, &QShortcut::activated, this, &Goingoutwithabang::undoModeB);
	QObject::connect(this->shortcutRedoModeB, &QShortcut::activated, this, &Goingoutwithabang::redoModeB);

	QObject::connect(this->ui.addPushButton, &QPushButton::clicked, this, &Goingoutwithabang::addTape);
	QObject::connect(this->ui.removePushButton, &QPushButton::clicked, this, &Goingoutwithabang::deleteTape);
	QObject::connect(this->ui.updatePushButton, &QPushButton::clicked, this, &Goingoutwithabang::updateTape);
	QObject::connect(this->ui.undoPushButton, &QPushButton::clicked, this, &Goingoutwithabang::undoModeA);
	QObject::connect(this->ui.redoPushButton, &QPushButton::clicked, this, &Goingoutwithabang::redoModeA);

	QObject::connect(this->ui.nextPushButton, &QPushButton::clicked, this, &Goingoutwithabang::nextWatchList);
	QObject::connect(this->ui.filterPushButton, &QPushButton::clicked, this, &Goingoutwithabang::filterList);
	QObject::connect(this->ui.openFilePushButton, &QPushButton::clicked, this, &Goingoutwithabang::showList);
	QObject::connect(this->ui.savePushButton, &QPushButton::clicked, this, &Goingoutwithabang::addOnWatchList);
	QObject::connect(this->ui.undoModeBPushButton, &QPushButton::clicked, this, &Goingoutwithabang::undoModeB);
	QObject::connect(this->ui.redoModeBPushButton, &QPushButton::clicked, this, &Goingoutwithabang::redoModeB);
	QObject::connect(this->ui.openTablePushButton, &QPushButton::clicked, this, &Goingoutwithabang::openTable);
}

void Goingoutwithabang::createShortcuts()
{
	this->shortcutUndoModeA = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_A), this);
	this->shortcutUndoModeB = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_B), this);
	this->shortcutRedoModeA = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_C), this);
	this->shortcutRedoModeB = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_D), this);
}

int Goingoutwithabang::getSelectedIndexModeA() const
{
	QModelIndexList selectedIndices = this->ui.tapesModeAListWidget->selectionModel()->selectedIndexes();
	if (selectedIndices.size() == 0)
	{
		this->ui.titleLineEdit->clear();
		this->ui.sectionLineEdit->clear();
		this->ui.dateLineEdit->clear();
		this->ui.accessCountLineEdit->clear();
		this->ui.footagePreviewLineEdit->clear();
		return -1;
	}
	int selectedIndex = selectedIndices.at(0).row();
	return selectedIndex;
}

int Goingoutwithabang::getSelectedIndexModeB() const
{
	QModelIndexList selectedIndices = this->ui.tapesModeBListWidget->selectionModel()->selectedIndexes();
	if (selectedIndices.size() == 0)
	{
		this->ui.titleLineEdit->clear();
		this->ui.sectionLineEdit->clear();
		this->ui.dateLineEdit->clear();
		this->ui.accessCountLineEdit->clear();
		this->ui.footagePreviewLineEdit->clear();
		return -1;
	}
	int selectedIndex = selectedIndices.at(0).row();
	return selectedIndex;
}

void Goingoutwithabang::addTape()
{
	std::string title = this->ui.titleLineEdit->text().toStdString();
	if (title.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid title!");
		return;
	}
	std::string section = this->ui.sectionLineEdit->text().toStdString();
	if (section.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid section!");
		return;
	}
	std::string dateOfCreation = this->ui.dateLineEdit->text().toStdString();
	if (dateOfCreation.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid date of creation!");
		return;
	}
	int accessCount = std::stoi(this->ui.accessCountLineEdit->text().toStdString());
	if (accessCount < 0)
	{
		QMessageBox::critical(this, "Error", "Invalid access count!");
		return;
	}
	std::string footagePreview = this->ui.footagePreviewLineEdit->text().toStdString();
	if (footagePreview.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid footage preview!");
		return;
	}

	std::size_t positionOfSpace = dateOfCreation.find("-");
	int month = stoi(dateOfCreation.substr(0, positionOfSpace));
	dateOfCreation.erase(0, positionOfSpace + 1);
	positionOfSpace = dateOfCreation.find("-");
	int day = stoi(dateOfCreation.substr(0, positionOfSpace));
	dateOfCreation.erase(0, positionOfSpace + 1);
	int year = stoi(dateOfCreation);

	try
	{
		this->service.addService(title, section, month, day, year, accessCount, footagePreview);
	}
	catch (RepositoryException& repositoryException)
	{
		QMessageBox::critical(this, "Error", repositoryException.what());
		return;
	}
	catch (ValidationException& validationException)
	{
		QMessageBox::critical(this, "Error", validationException.what());
		return;
	}
}

void Goingoutwithabang::deleteTape()
{
	std::string title = this->ui.titleLineEdit->text().toStdString();
	if (title.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid title!");
		return;
	}
	try
	{
		this->service.deleteService(title);
	}
	catch (RepositoryException& repositoryException)
	{
		QMessageBox::critical(this, "Error", repositoryException.what());
		return;
	}
}

void Goingoutwithabang::updateTape()
{
	std::string title = this->ui.titleLineEdit->text().toStdString();
	if (title.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid title!");
		return;
	}
	std::string section = this->ui.sectionLineEdit->text().toStdString();
	if (section.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid section!");
		return;
	}
	std::string dateOfCreation = this->ui.dateLineEdit->text().toStdString();
	if (dateOfCreation.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid date of creation!");
		return;
	}
	int accessCount = std::stoi(this->ui.accessCountLineEdit->text().toStdString());
	if (accessCount < 0)
	{
		QMessageBox::critical(this, "Error", "Invalid access count!");
		return;
	}
	std::string footagePreview = this->ui.footagePreviewLineEdit->text().toStdString();
	if (footagePreview.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid footage preview!");
		return;
	}

	std::size_t positionOfSpace = dateOfCreation.find("-");
	int month = stoi(dateOfCreation.substr(0, positionOfSpace));
	dateOfCreation.erase(0, positionOfSpace + 1);
	positionOfSpace = dateOfCreation.find("-");
	int day = stoi(dateOfCreation.substr(0, positionOfSpace));
	dateOfCreation.erase(0, positionOfSpace + 1);
	int year = stoi(dateOfCreation);
	try
	{
		this->service.updateService(title, section, month, day, year, accessCount, footagePreview);
	}
	catch (RepositoryException& repositoryException)
	{
		QMessageBox::critical(this, "Error", repositoryException.what());
		return;
	}
	catch (ValidationException& validationException)
	{
		QMessageBox::critical(this, "Error", validationException.what());
		return;
	}
}

void Goingoutwithabang::addOnWatchList()
{
	std::string title = this->ui.titleModeBLineEdit->text().toStdString();
	if (title.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid title!");
		return;
	}
	try
	{
		this->service.addTapeOnWatchList(title);
		this->table->update();
		
	}
	catch (RepositoryException& repositoryException)
	{
		QMessageBox::critical(this, "Error", repositoryException.what());
		return;
	}
	catch (ValidationException& validationException)
	{
		QMessageBox::critical(this, "Error", validationException.what());
		return;
	}
}

void Goingoutwithabang::nextWatchList()
{
	this->ui.tapesModeBListWidget->setCurrentRow(position);
	this->service.next(position);
}

void Goingoutwithabang::showList()
{
	this->service.myList();
}

void Goingoutwithabang::filterList()
{
	std::string accessCountString = this->ui.accessCountFilterLineEdit->text().toStdString();
	std::string section = this->ui.sectionFilterLineEdit->text().toStdString();
	if (accessCountString == "" || section == "")
	{
		this->populateList();
	}
	else {
		int accessCount = std::stoi(accessCountString);
		if (accessCount < 0)
		{
			QMessageBox::critical(this, "Error", "Invalid access count!");
			return;
		}

		if (section.empty())
		{
			QMessageBox::critical(this, "Error", "Invalid section!");
			return;
		}
		this->ui.tapesModeBListWidget->clear();
		std::vector<Tape> allTapes = this->service.list(section, accessCount);
		for (auto tape : allTapes)
		{
			std::string date{ "" };
			date += std::to_string(tape.getDate().getMonth()) + "-" + std::to_string(tape.getDate().getDay()) + "-" + std::to_string(tape.getDate().getYear());
			this->ui.tapesModeBListWidget->addItem(QString::fromStdString(tape.getTitle() + ", " + tape.getSection() + ", " + date + ", " + std::to_string(tape.getAccessCount())
				+ ", " + tape.getFootagePreview()));
		}
	}
}

void Goingoutwithabang::openTable()
{
	this->table->show();
}

void Goingoutwithabang::undoModeA()
{
	try {
		this->service.undoLastActionModeA();
	}
	catch (ValidationException& validationException)
	{
		QMessageBox::critical(this, "Error", validationException.what());
		return;
	}
}

void Goingoutwithabang::redoModeA()
{
	try {
		this->service.redoLastActionModeA();
	}
	catch (ValidationException& validationException)
	{
		QMessageBox::critical(this, "Error", validationException.what());
		return;
	}
}

void Goingoutwithabang::undoModeB()
{
	try {
		this->service.undoLastActionModeB();
		this->table->update();
	}
	catch (ValidationException& validationException)
	{
		QMessageBox::critical(this, "Error", validationException.what());
		return;
	}
}

void Goingoutwithabang::redoModeB()
{
	try {
		this->service.redoLastActionModeB();
		this->table->update();
	}
	catch (ValidationException& validationException)
	{
		QMessageBox::critical(this, "Error", validationException.what());
		return;
	}
}
