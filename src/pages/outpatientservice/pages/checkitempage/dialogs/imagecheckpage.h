#pragma once

#include "defaultpage.h"

class ImageCheckPage : public DefaultPage
{
    Q_OBJECT

public:
    explicit ImageCheckPage(QWidget* parent = nullptr);

    void initUi() override;

};

