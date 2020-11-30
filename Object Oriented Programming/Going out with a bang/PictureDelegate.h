#pragma once
#include <QStyledItemDelegate>
#include "Repository.h"

class PictureDelegate : public QStyledItemDelegate
{
public:
	PictureDelegate(QWidget* parent = Q_NULLPTR);

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

};

