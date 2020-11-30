#pragma once
#include <qabstractitemmodel.h>
#include "Repository.h"
#include "Observer.h"

class TapesListModel :
	public QAbstractListModel, public Observer
{
private:
	Repository<Idea>& repository;

public:
	TapesListModel(Repository<Idea>& newRepository) : repository{ newRepository } {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	void update();
};

