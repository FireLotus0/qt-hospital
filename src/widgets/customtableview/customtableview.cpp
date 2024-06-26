#include "customtableview.h"

CustomTableView::CustomTableView(QWidget *parent)
    : QTableView(parent)
{
    model = new QStandardItemModel(this);

    verticalHeader = new HeaderDelegate(Qt::Vertical, this);
    horizontalHeader = new HeaderDelegate(Qt::Horizontal, this);

    setVerticalHeader(verticalHeader);
    setHorizontalHeader(horizontalHeader);

    tableViewDelegate = new TableViewDelegate(this);
    setItemDelegate(tableViewDelegate);

    QTableView::setModel(model);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}


void CustomTableView::setHorizontalHeaderLabels(const QStringList &names) {
    model->setHorizontalHeaderLabels(names);
}

void CustomTableView::insertModelData(const QVariantList &data) {
    auto count = model->rowCount();
    QList<QStandardItem*> items;
    for(int col = 0; col < data.count(); col++) {
        const auto& value = data.at(col);
        auto item = new QStandardItem;
        item->setText(value.toString());
        item->setTextAlignment(Qt::AlignCenter);
        items.append(item);
    }
    model->insertRow(count, items);

    //设置垂直表头值
    auto headerData = new QStandardItem;
    headerData->setText(QString("%1").arg(count + 1, 2, 10, QChar('0')));
    model->setVerticalHeaderItem(count, headerData);
}

void CustomTableView::setHeaderViewControl(Qt::Orientation orientation, int index, bool visible) {
    if(orientation == Qt::Vertical) {
        verticalHeader->setHeaderControl(index, visible);
    } else {
        horizontalHeader->setHeaderControl(index, visible);
    }
}

void CustomTableView::setTableViewColumnColor(int column, const QColor &color) {
    tableViewDelegate->setColumColor(column, color);
}

QStandardItemModel *CustomTableView::getModel()
{
    return model;
}
