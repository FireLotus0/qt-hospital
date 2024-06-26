#pragma once

#include "defaultpage.h"

class OtherCheckPage : public DefaultPage
{
    Q_OBJECT

public:
    explicit OtherCheckPage(QWidget* parent = nullptr);

    void initUi() override;
};

