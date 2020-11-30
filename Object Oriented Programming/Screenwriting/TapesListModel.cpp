#include "TapesListModel.h"

int TapesListModel::rowCount(const QModelIndex& parent) const
{
	return this->repository.getAll().size();
}

QVariant TapesListModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	Idea currentEntity = this->repository.getAll()[row];
	int column = index.column();
	if (role == Qt::DisplayRole)
	{
		/*std::string date{ "" };
		date += std::to_string(currentTape.getDate().getMonth()) + "-" + std::to_string(currentTape.getDate().getDay()) + "-" + std::to_string(currentTape.getDate().getYear());
		return QString::fromStdString(currentTape.getTitle() + " " + currentTape.getSection() + " " + date + " " + std::to_string(currentTape.getAccessCount()) 
			+ " " + currentTape.getFootagePreview());*/
	}
	return QVariant();
}

void TapesListModel::update()
{
}
