#pragma once

#include "defaultpage.h"

class LaboratoryCheckPage : public DefaultPage
{
    Q_OBJECT

public:
    explicit LaboratoryCheckPage(QWidget* parent = nullptr);

    void initUi() override;
};

