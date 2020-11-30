#include "TableModel.h"

/*int TapesTableModel::rowCount(const QModelIndex& parent) const
{
	return this->repository.getSizeOfRepository();
}

int TapesTableModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant TapesTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	std::vector<Idea> ideas = this->repository.getAll();
	std::sort(ideas.begin(), ideas.end(), [](const Idea& a, const Idea& b) {return (a.getAct() < b.getAct()); });
	Idea currentEntity = ideas[row];
	int column = index.column();
	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(currentEntity.getDescription());
		case 1:
			return QString::fromStdString(currentEntity.getStatus());
		case 2:
		{
			return QString::fromStdString(currentEntity.getCreator());
		}
		case 3:
			return QString::number(currentEntity.getAct());
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
				return QString("Description");
			case 1:
				return QString("Status");
			case 2:
				return QString("Creator");
			case 3:
				return QString("Act");
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
}*/
