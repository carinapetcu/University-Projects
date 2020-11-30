#pragma once
#include <qabstractitemmodel.h>
#include "Repository.h"
#include "Domain.h"
#include <string>
#include "Observer.h"

/*class TapesTableModel : public QAbstractTableModel, public Observer
{
private:
	Repository<Idea>& repository;

public:
	TapesTableModel(Repository<Idea>& newRepository) : repository{ newRepository } {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	void update();
};*/

