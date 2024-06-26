#include "tableviewdelegate.h"

#include <qpainter.h>

TableViewDelegate::TableViewDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}
//void TableViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
//    auto text = index.data(Qt::EditRole).toString();
//    auto color = columnColorHash.value(index.column());
//    if(color.isValid()) {
//        painter->setPen(color);
//    } else {
//        painter->setPen(QColor(0x1D2129));
//    }
//    painter->drawText(option.rect, Qt::AlignCenter, text);
//}

void TableViewDelegate::setColumColor(int column, const QColor &color) {
    columnColorHash.insert(column, color);
}
