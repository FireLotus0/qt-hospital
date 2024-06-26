#include "findposhelper.h"

QPoint FindPosHelper::findParentWidgetBottomGlobalPos(QWidget* widget) {
    QWidget* topWidget = widget->parentWidget();
    if(!topWidget) {
        return widget->pos() + QPoint(widget->height(), 0);
    }
    QPoint pos;

    while(topWidget->parentWidget()) {
        pos += topWidget->pos();
        topWidget = topWidget->parentWidget();
    }
    pos += topWidget->pos();
    pos += {0, widget->parentWidget()->height()};
    return pos;
}
QPoint FindPosHelper::findParentWidgetBottomGlobalPos(QWidget *widget, int parentWidgetNumber, int offset) {
    for(int i = parentWidgetNumber; i > 0; i--) {
        widget = widget->parentWidget();
        if(!widget) {
            return widget->pos() + QPoint(0, widget->height() + offset);
        }
    }
    QWidget* targetWidget = widget;
    QPoint pos;
    while(widget->parentWidget()) {
        pos += widget->pos();
        widget = widget->parentWidget();
    }
    pos += widget->pos();
    pos += {0, targetWidget->height() + offset};
    return pos;
}
