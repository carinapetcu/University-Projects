#include "Quiz.h"

Quiz::Quiz(Service& service, Participant participant, QWidget *parent)
    : service(service), participant(participant), QMainWindow(parent)
{
    ui.setupUi(this);
	this->populateList();
	this->connectSignalsAndSlots();
	this->ui.scoreLineEdit->setText(QString::number(participant.getScore()));
	this->ui.scoreLineEdit->setEnabled(false);
}

void Quiz::populateList()
{
	this->ui.questionListWidget->clear();
	std::vector<Question> allQuestions = this->service.getAllSortedByScore();
	for (auto question : allQuestions)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(std::to_string(question.getId()) + " - " + question.getText() + " - " + std::to_string(question.getScore())));
		if(this->service.isAnswered(participant.getName(), question.getId())) item->setBackground(Qt::green); // sets green background
		this->ui.questionListWidget->addItem(item);
	}
}

void Quiz::connectSignalsAndSlots()
{
	QObject::connect(this->ui.answerPushButton, &QPushButton::clicked, this, &Quiz::answerQuestion);
	QObject::connect(this->ui.questionListWidget, &QListWidget::itemSelectionChanged, this, &Quiz::setAnswerButton);
}

void Quiz::update()
{
	this->populateList();
	
}

void Quiz::answerQuestion()
{
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex != -1)
	{
		this->service.addAnswered(this->participant.getName(), this->service.getAllSortedByScore()[selectedIndex].getId());
		this->ui.answerPushButton->setEnabled(false);
		// now we check if the answer is correct
		std::string answer = this->ui.answerLineEdit->text().toStdString();
		if (answer == this->service.getAllSortedByScore()[selectedIndex].getCorrectAnswer())
		{
			this->service.updateParticipant(participant.getName(), participant.getScore() + this->service.getAllSortedByScore()[selectedIndex].getScore());
			this->participant.setScore(this->participant.getScore() + this->service.getAllSortedByScore()[selectedIndex].getScore());
			this->ui.scoreLineEdit->setText(QString::number(this->participant.getScore()));
		}
	}
}

void Quiz::setAnswerButton()
{
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex != -1)
	{
		if (this->service.isAnswered(this->participant.getName(), this->service.getAllSortedByScore()[selectedIndex].getId()))
			this->ui.answerPushButton->setEnabled(false);
		else
			this->ui.answerPushButton->setEnabled(true);
	}
}

int Quiz::getSelectedIndex() const
{
	QModelIndexList selectedIndices = this->ui.questionListWidget->selectionModel()->selectedIndexes();
	if (selectedIndices.size() == 0)
	{
		return -1;
	}
	int selectedIndex = selectedIndices.at(0).row();
	return selectedIndex;
}
