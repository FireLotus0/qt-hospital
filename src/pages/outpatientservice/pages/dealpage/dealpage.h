#pragma once

#include "ui_dealpage.h"
#include <QWidget>

class DealPage : public QWidget
{
    Q_OBJECT

public:
    DealPage(QWidget* parent = nullptr);


private:
    Ui::DealPage ui{};

private slots:

    void on_btn_commit_hospital_clicked();

    void on_btn_commit_verify_clicked();

    void on_btn_print_hospital_clicked();

    void on_btn_print_verify_clicked();


};
