#include "Search.h"

Search::Search(Service& service, QWidget *parent)
	: service(service), QWidget(parent)
{
	ui.setupUi(this);
	this->connectSignalsAndSlots();
}

Search::~Search()
{
}

void Search::connectSignalsAndSlots()
{
	QObject::connect(this->ui.searchLineEdit, &QLineEdit::textChanged, this, &Search::filterList);
}

void Search::filterList()
{
	this->ui.matchingTreeWidget->clear();
	this->ui.matchingTreeWidget->setColumnCount(1);
	std::string filter = this->ui.searchLineEdit->text().toStdString();
	std::vector<std::string> answers = this->service.getAllAnswers(filter);
	QTreeWidgetItem* treeItem = new QTreeWidgetItem(this->ui.matchingTreeWidget);
	if (answers.size() > 0) {
		treeItem->setText(0, QString::fromStdString(answers[0]));
		for (int index = 1; index < answers.size(); index++)
		{
			QTreeWidgetItem* treeChild = new QTreeWidgetItem();
			treeChild->setText(0, QString::fromStdString(answers[index]));
			treeItem->addChild(treeChild);
		}
	}
}

void Search::update()
{
	this->filterList();
}
