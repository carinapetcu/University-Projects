#include "TableModel.h"

int TableModel::rowCount(const QModelIndex& parent) const
{
	return this->repository.getSizeOfRepository();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	std::vector<Star> stars = this->repository.getAll();
	Star currentEntity = stars[row];
	int column = index.column();
	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(currentEntity.getName());
		case 1:
			return QString::number(currentEntity.getRA());
		case 2:
		{
			return QString::number(currentEntity.getDec());
		}
		case 3:
			return QString::number(currentEntity.getDiameter());
		case 4:
			return QString::fromStdString(currentEntity.getConstellation());
		default:
			break;
		}

	}
	return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0: 
				return QString("Name");
			case 1:
				return QString("Right Ascension");
			case 2:
				return QString("Declination");
			case 3:
				return QString("Diameter");
			default:
				break;
			}
		}
	}
	return QVariant();
}

void TableModel::update()
{
	QModelIndex topLeft = this->index(1, 1);
	QModelIndex bottomRight = this->index(this->rowCount(), this->columnCount());
	emit layoutChanged();
	emit dataChanged(topLeft, bottomRight);
}