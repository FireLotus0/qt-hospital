#pragma once

#include "ui_patientselect.h"

#include <QWidget>
#include <QStandardItemModel>

class PatientSelect : public  QWidget
{
    Q_OBJECT

public:
    PatientSelect(QWidget* parent = nullptr);

private:
    void initTable();

private slots:
    void on_btn_date_start_clicked();

    void on_btn_date_end_clicked();

private:
    Ui::PatientSelect ui{};
    QStandardItemModel* model;
};
