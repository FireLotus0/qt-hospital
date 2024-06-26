#pragma once

#include "ui_checkitem.h"

#include <QWidget>

class CheckItem : public QWidget
{
    Q_OBJECT
public:
    explicit CheckItem(QWidget *parent = nullptr);

    void setContent(QStringList data);
private:
    Ui::CheckItem ui;
};


