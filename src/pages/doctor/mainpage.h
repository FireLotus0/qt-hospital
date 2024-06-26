#pragma once

#include "ui_mainpage.h"

#include <QWidget>
#include <QStandardItemModel>

enum PageType
{
    DoctorWord,
    Check,
    Inspect,
    Operation,
    SelectPatient
};

class MainPage : public  QWidget
{
    Q_OBJECT

public:
    MainPage(QWidget* parent = nullptr);

private:
    void initTree();

    void initSignalSlots();

    void initStackWidget();
private:
    Ui::MainPage ui{};
    QStandardItemModel* model;
};
