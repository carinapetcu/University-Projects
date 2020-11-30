#include "TapesTableModel.h"

int TapesTableModel::rowCount(const QModelIndex& parent) const
{
	return this->repository.getSizeOfRepository();
}

int TapesTableModel::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant TapesTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	Tape currentTape = this->repository.getAll()[row];
	int column = index.column();
	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(currentTape.getTitle());
		case 1:
			return QString::fromStdString(currentTape.getSection());
		case 2:
		{
			std::string date{ "" };
			date += std::to_string(currentTape.getDate().getMonth()) + "-" + std::to_string(currentTape.getDate().getDay()) + "-" + std::to_string(currentTape.getDate().getYear());
			return QString::fromStdString(date);
		}
		case 3:
			return QString::number(currentTape.getAccessCount());
		case 4:
			return QString::fromStdString(currentTape.getFootagePreview());
		default:
			break;
		}

	}
	return QVariant();
}

QVariant TapesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0: 
				return QString("Title");
			case 1:
				return QString("Section");
			case 2:
				return QString("Date of creation");
			case 3:
				return QString("Access count");
			case 4:
				return QString("Footage preview");
			default:
				break;
			}
		}
	}
	return QVariant();
}

void TapesTableModel::update()
{
	QModelIndex topLeft = this->index(1, 1);
	QModelIndex bottomRight = this->index(this->rowCount(), this->columnCount());
	emit layoutChanged();
	emit dataChanged(topLeft, bottomRight);
}
