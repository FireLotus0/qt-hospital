#pragma once

#include "ui_medicinewidget.h"

#include <QWidget>
#include <QMouseEvent>

class MedicineWidget: public QWidget
{
    Q_OBJECT

public:
    explicit MedicineWidget(int id, QWidget* parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;

    int getId() { return id; }

    // 药品名，价格，特殊说明
    void setText(const QStringList& info);

    void initSigSlots();
signals:
    void deleteMedicine(int);

    void widgetClicked(MedicineWidget*);
private:
    Ui::MedicineWidget ui{};
    int id;
};
