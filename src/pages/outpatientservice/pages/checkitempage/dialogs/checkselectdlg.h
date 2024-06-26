#pragma once

#include "pages/basedialog/basedialog.h"
#include "appsetting.h"

class CheckSelectDlg : public BaseDialog
{
    Q_OBJECT

public:
    explicit CheckSelectDlg(QWidget *parent = nullptr);

    void initPageData();

public slots:
    void on_btn_confirm_clicked();

signals:
    void confirmed(CheckProject);
};
