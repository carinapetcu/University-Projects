#include "Presenter.h"
#include <qmessagebox.h>

Presenter::Presenter(Service& service, QWidget *parent)
	:service(service), QWidget(parent)
{
	ui.setupUi(this);
	this->ui.questionsListWidget->setSortingEnabled(true);
	this->populateList();
	this->connectSignalsAndSlots();
}

Presenter::~Presenter()
{
}

void Presenter::populateList()
{ 
	this->ui.questionsListWidget->clear();
	std::vector<Question> allQuestions = this->service.getAllQuestions();
	for (auto question : allQuestions)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(std::to_string(question.getId()) + " - " + question.getText() + " - " + question.getCorrectAnswer()  + " - " + std::to_string(question.getScore())));
		this->ui.questionsListWidget->addItem(item);
	}
	this->ui.questionsListWidget->sortItems();
}

void Presenter::connectSignalsAndSlots()
{
	QObject::connect(this->ui.addQuestionPushButton, &QPushButton::clicked, this, &Presenter::addQuestion);
}

void Presenter::update()
{
	this->populateList();
}

void Presenter::addQuestion()
{
	std::string text = this->ui.textLineEdit->text().toStdString();
	if (text.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid text!");
		return;
	}
	std::string correctAnswer = this->ui.correctAnswerLineEdit->text().toStdString();
	if (correctAnswer.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid correct answer!");
		return;
	}
	std::string idString = this->ui.idLineEdit->text().toStdString();
	if (idString.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid id!");
		return;
	}
	int id = std::stoi(idString);
	try
	{
		this->service.addQuestion(id, text, correctAnswer, 0);
	}
	catch (RepositoryException& repositoryException)
	{
		QMessageBox::critical(this, "Error", repositoryException.what());
		return;
	}
}
