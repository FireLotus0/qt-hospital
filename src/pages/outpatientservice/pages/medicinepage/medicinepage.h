#pragma once

#include <QWidget>

#include "widgets/medicinewidget.h"
#include "ui_medicinepage.h"
#include "appsetting.h"

class MedicinePage : public QWidget
{
    Q_OBJECT

public:
    explicit MedicinePage(QWidget* parent);
    ~MedicinePage();

public slots:
    void on_btn_query_clicked();

private:
    void iniUi();

    void parseQuery(const QList<QJsonObject>& list);

    void clearTable();

    void initSigSlots();

    void updateWidget(MedicineWidget* cur);

    void initSheet();

    void setInfoText(int id);

private slots:
    void on_btn_commit_clicked();

private:
    Ui::MedicinePage ui{};
    QHash<int, MedicineWidget*> medicineList;
    QHash<int, Medicine> dataList;
    QList<Medicine> queryList;
    MedicineWidget* lastWidget;

    QString normalSheet;
    QString selectedSheet;
};
