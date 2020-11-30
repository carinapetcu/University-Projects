#pragma once
#include <qabstractitemmodel.h>
#include "Repository.h"

class TapesListModel :
	public QAbstractListModel
{
private:
	Repository<Tape>& repository;

public:
	TapesListModel(Repository<Tape>& newRepository) : repository{ newRepository } {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
};

