#include "IssueTracker.h"
#include <qmessagebox.h>
#include "Exceptions.h"

IssueTracker::IssueTracker(Service& service, User user, QWidget *parent)
    : service(service), user(user), QMainWindow(parent)
{
    ui.setupUi(this);
    this->populateList();
    this->connectSignalsAndSlots();
	if (this->user.getType() == "programmer")
		this->ui.addIssuePushButton->setEnabled(false);
	this->ui.resolveIssuePushButton->setEnabled(false);
}

void IssueTracker::populateList()
{
	this->ui.issuesListWidget->clear();

	std::vector<Issue> allIssues = this->service.getAllIssues();
	for (auto issue : allIssues)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(issue.getDescription() + " - " + issue.getStatus() + " - " + issue.getReporter() + " - " + issue.getSolver()));
		this->ui.issuesListWidget->addItem(item);
	}
}

void IssueTracker::connectSignalsAndSlots()
{
	QObject::connect(this->ui.issuesListWidget, &QListWidget::itemSelectionChanged, this, &IssueTracker::activateOrDeactivateResolve);
	QObject::connect(this->ui.addIssuePushButton, &QPushButton::clicked, this, &IssueTracker::addIssue);
	QObject::connect(this->ui.removeIssuePushButton, &QPushButton::clicked, this, &IssueTracker::removeIssue);
	QObject::connect(this->ui.resolveIssuePushButton, &QPushButton::clicked, this, &IssueTracker::updateIssue);
}

void IssueTracker::update()
{
	this->populateList();
}

void IssueTracker::addIssue()
{
	std::string description = this->ui.issueDescriptionLineEdit->text().toStdString();
	if (description.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid issue!");
		return;
	}
	try {
		this->service.addIssue(description, this->user.getName());
	}
	catch (const RepositoryException exception)
	{
		QMessageBox::critical(this, "Error", exception.what());
		return;
	}
}

void IssueTracker::removeIssue()
{
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex != -1) {
		try {
			this->service.removeIssue(this->service.getAllIssues()[selectedIndex].getDescription());
		}
		catch (const RepositoryException exception)
		{
			QMessageBox::critical(this, "Error", exception.what());
			return;
		}
		catch (const ServiceException exception)
		{
			QMessageBox::critical(this, "Error", exception.what());
			return;
		}
	}
}

void IssueTracker::updateIssue()
{
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex != -1) {
		try {
			this->service.resolveIssue(this->service.getAllIssues()[selectedIndex].getDescription(), this->user.getName());
		}
		catch (const RepositoryException exception)
		{
			QMessageBox::critical(this, "Error", exception.what());
			return;
		}
		catch (const ServiceException exception)
		{
			QMessageBox::critical(this, "Error", exception.what());
			return;
		}
	}
}

void IssueTracker::activateOrDeactivateResolve()
{
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex != -1 && this->service.getAllIssues()[selectedIndex].getStatus() == "open" && this->user.getType() == "programmer")
		this->ui.resolveIssuePushButton->setEnabled(true);
}

int IssueTracker::getSelectedIndex() const
{
	QModelIndexList selectedIndices = this->ui.issuesListWidget->selectionModel()->selectedIndexes();
	if (selectedIndices.size() == 0)
	{
		return -1;
	}
	int selectedIndex = selectedIndices.at(0).row();
	return selectedIndex;
}
