#pragma once

#include <qstyleditemdelegate.h>

class TableViewDelegate : public QStyledItemDelegate
{
public:
    explicit TableViewDelegate(QObject* parent = nullptr);

   // void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setColumColor(int column, const QColor& color);

private:
    QHash<int, QColor> columnColorHash;
};
