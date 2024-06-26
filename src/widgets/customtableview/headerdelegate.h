#pragma once

#include <qheaderview.h>
#include <qabstractbutton.h>
#include <qapplication.h>
#include <qcombobox.h>
#include <qstyleditemdelegate.h>
#include <qdebug.h>

class HeaderDelegate : public QHeaderView
{
    Q_OBJECT
public:
    explicit HeaderDelegate(Qt::Orientation orientation, QWidget* parent = nullptr);

    void setHeaderControl(int index, bool visible);

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;

private slots:
    void onComboBoxChanged(const QString& text);

private:
    QComboBox* comboBox;

    int comBoxIndex = -1;           //下拉列表索引
    bool isDropdownVisible = false; //下拉列表是否可见
};