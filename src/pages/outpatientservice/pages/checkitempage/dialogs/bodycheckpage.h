#pragma once

#include "defaultpage.h"

class BodyCheckPage : public DefaultPage
{
    Q_OBJECT

public:
    explicit BodyCheckPage(QWidget* parent = nullptr);

    void initUi() override;
};
