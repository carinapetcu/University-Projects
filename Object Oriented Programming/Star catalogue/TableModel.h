#pragma once
#include <qabstractitemmodel.h>
#include "Repository.h"
#include "Domain.h"
#include <string>
#include "Observer.h"

class TableModel : public QAbstractTableModel, public Observer
{
private:
	Repository<Star>& repository;

public:
	TableModel(Repository<Star>& newRepository) : repository{ newRepository } {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	void update();
};

