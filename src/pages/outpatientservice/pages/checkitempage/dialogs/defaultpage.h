#pragma once

#include "ui_defaultpage.h"
#include "appsetting.h"

class DefaultPage : public QWidget
{
    Q_OBJECT

public:
    explicit DefaultPage(QWidget* parent = nullptr);

    virtual void initUi();

    virtual CheckProject getContent();

    Ui::DefaultPage ui{};
};
