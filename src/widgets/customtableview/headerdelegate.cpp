#include "headerdelegate.h"

#include <qpainter.h>
#include <qdebug.h>
#include <qevent.h>
#include <qrect.h>

HeaderDelegate::HeaderDelegate(Qt::Orientation orientation, QWidget* parent)
    : QHeaderView(orientation, parent)
{
    if(orientation == Qt::Horizontal) {
        setSectionResizeMode(QHeaderView::Stretch);
        setFixedHeight(42);
    } else {
        QHeaderView::setVisible(false);
        setFixedWidth(43);
    }

    setSectionsClickable(true);
}

void HeaderDelegate::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const {
    QPen pen;
    pen.setColor(QColor(0xE9EEF5));
    pen.setWidth(1);
    painter->setPen(pen);
    painter->setBrush(QColor(0xBECFE6));
    QRect headerRect;
    if(orientation() == Qt::Vertical) {
        headerRect = rect.adjusted(-1, 0, 0, 0);
    } else {
        headerRect = rect.adjusted(0, -1, 0, 0);
    }
    painter->drawRect(headerRect);
    painter->setPen(QColor(0x4E5969));

    //绘制数据
    auto drawData = model()->headerData(logicalIndex, orientation()).toString();

    //追加数据
    auto roleData = model()->headerData(logicalIndex, orientation(), Qt::UserRole + 1);
    if(!roleData.isNull()) {
        drawData.append("(" + roleData.toString() + ")");
    }

    //对齐方式
    Qt::Alignment alignment = Qt::AlignCenter;
    if(comBoxIndex == logicalIndex) {
        alignment = Qt::AlignLeft | Qt::AlignVCenter;
        headerRect = headerRect.adjusted(8, 0, 0, 0);
    }

    painter->drawText(headerRect, alignment, drawData);

    if(isDropdownVisible) {
        //绘制下拉按钮
        if(comBoxIndex == logicalIndex) {     //逻辑索引位置
            comboBox->setGeometry(headerRect);

            QStyleOptionComboBox combox;
            combox.initFrom(comboBox);
            combox.rect = headerRect;

            style()->drawComplexControl(QStyle::CC_ComboBox, &combox, painter, comboBox);
        }
    }

}

void HeaderDelegate::setHeaderControl(int index, bool visible) {
    comBoxIndex = index;
    isDropdownVisible = visible;
}

void HeaderDelegate::onComboBoxChanged(const QString &text) {
    model()->setHeaderData(comBoxIndex, orientation(), text, Qt::UserRole + 1);
}
