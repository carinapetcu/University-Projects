#include "QuestionAndAnswerSite.h"
#include <qmessagebox.h>

QuestionAndAnswerSite::QuestionAndAnswerSite(Service& service, std::string name, QWidget *parent)
    : service(service), name(name), QMainWindow(parent)
{
    ui.setupUi(this);
	this->populateList();
	this->connectSignalsAndSlots();
}

void QuestionAndAnswerSite::populateList()
{
	this->ui.questionsListWidget->clear();

	std::vector<Question> allQuestions = this->service.getAllQuestions();
	for (auto question : allQuestions)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(question.getText()));
		//if(question.getName() == name) item->setBackground(Qt::yellow); // sets green background
		this->ui.questionsListWidget->addItem(item);
	}
}

void QuestionAndAnswerSite::connectSignalsAndSlots()
{
	QObject::connect(this->ui.addQuestionPushButton, &QPushButton::clicked, this, &QuestionAndAnswerSite::addQuestion);
	QObject::connect(this->ui.addAnswerPushButton, &QPushButton::clicked, this, &QuestionAndAnswerSite::addAnswer);
	QObject::connect(this->ui.questionsListWidget, &QListWidget::itemSelectionChanged, this, &QuestionAndAnswerSite::populateAnswersList);
	QObject::connect(this->ui.answersListWidget, &QListWidget::itemSelectionChanged, this, &QuestionAndAnswerSite::spinBox);
	QObject::connect(this->ui.votesSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &QuestionAndAnswerSite::changeVotes);
}

void QuestionAndAnswerSite::update()
{
	this->populateList();
	this->populateAnswersList();
}

void QuestionAndAnswerSite::addQuestion()
{
	std::string title = this->ui.newQuestionLineEdit->text().toStdString();
	if (title.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid question!");
		return;
	}
	this->service.addQuestion(title, this->name);
}

void QuestionAndAnswerSite::addAnswer()
{
	int selectedIndex = this->getSelectedIndex();
	std::string title = this->ui.newQuestionLineEdit->text().toStdString();
	if (title.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid answer!");
		return;
	}
	this->service.addAnswer(this->service.getAllQuestions()[selectedIndex].getId(), this->name, title, 0);
}

void QuestionAndAnswerSite::populateAnswersList()
{
	int selectedIndex = this->getSelectedIndex();
	std::vector<Answer> answers = this->service.getAnswers(this->service.getAllQuestions()[selectedIndex].getId());
	for (auto answer : answers)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(std::to_string(answer.getId()) + " - " + answer.getText() + " - " + std::to_string(answer.getVotes())));
		if (answer.getName() == name) item->setBackground(Qt::yellow);
		this->ui.answersListWidget->addItem(item);
	}
}

void QuestionAndAnswerSite::spinBox()
{
	int selectedIndex = this->getSelectedIndexAnswers();
	this->ui.votesSpinBox->setEnabled(true);
	if (selectedIndex != -1) {
		std::vector<Answer> answers = this->service.getAnswers(this->service.getAllQuestions()[selectedIndex].getId());
		if (answers[selectedIndex].getName() == name)
			this->ui.votesSpinBox->setEnabled(false);
		else
		{
			this->ui.votesSpinBox->setValue(answers[selectedIndex].getVotes());
			this->ui.votesSpinBox->setRange(answers[selectedIndex].getVotes() - 1, answers[selectedIndex].getVotes() + 1);
		}
	}
}

void QuestionAndAnswerSite::changeVotes()
{
	int selectedIndex = this->getSelectedIndexAnswers();
	std::vector<Answer> answers = this->service.getAnswers(this->service.getAllQuestions()[selectedIndex].getId());
	int votes = this->ui.votesSpinBox->value();
	answers[selectedIndex].setVotes(votes);
	this->service.updateAnswer(answers[selectedIndex]);
}

int QuestionAndAnswerSite::getSelectedIndex() const
{
	QModelIndexList selectedIndices = this->ui.questionsListWidget->selectionModel()->selectedIndexes();
	if (selectedIndices.size() == 0)
	{
		return -1;
	}
	int selectedIndex = selectedIndices.at(0).row();
	return selectedIndex;
}

int QuestionAndAnswerSite::getSelectedIndexAnswers() const
{
	QModelIndexList selectedIndices = this->ui.answersListWidget->selectionModel()->selectedIndexes();
	if (selectedIndices.size() == 0)
	{
		return -1;
	}
	int selectedIndex = selectedIndices.at(0).row();
	return selectedIndex;
}
