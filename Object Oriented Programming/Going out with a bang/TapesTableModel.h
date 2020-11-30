#pragma once
#include <qabstractitemmodel.h>
#include "Repository.h"
#include "Tape.h"
#include <string>

class TapesTableModel : public QAbstractTableModel
{
private:
	Repository<Tape>& repository;

public:
	TapesTableModel(Repository<Tape>& newRepository) : repository{ newRepository } {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	void update();
};

