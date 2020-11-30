#include "PictureDelegate.h"
#include <QPixmap>
#include <QPainter>
#include "Tape.h"

PictureDelegate::PictureDelegate(QWidget* parent) : QStyledItemDelegate{ parent }
{
}

void PictureDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QString organism = index.model()->data(index, Qt::EditRole).toString();

	if (index.column() != 4)
	{
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}

	QPixmap pixMap("button_play.jpg");
	painter->drawPixmap(option.rect, pixMap);
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() == 4)
	{
		return QSize(32, 32);
	}

	return QStyledItemDelegate::sizeHint(option, index);
}
