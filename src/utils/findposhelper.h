#pragma once

#include <QWidget>

class FindPosHelper{
public:
    static QPoint findParentWidgetBottomGlobalPos(QWidget* widget);

    static QPoint findParentWidgetBottomGlobalPos(QWidget *widget, int parentWidgetNumber, int offset);
};
