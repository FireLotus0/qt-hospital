#pragma once

#include "utils/windowframelesshelper.h"
#include "ui_progressbardlg.h"

#include <qdialog.h>
#include <qpainter.h>
#include <qstyleoption.h>

class ProgressBarDlg : public WindowFramelessWidget<QDialog>
{
    Q_OBJECT

public:
    /**
     * @消息提示对话框
     * @param val 进度条初始数值
     * @param parent
     * @return
     */
    static ProgressBarDlg* showDlg(int val, QWidget *parent = nullptr);

    void setValue(int val);

    void paintEvent(QPaintEvent* event) override;

private:
    explicit ProgressBarDlg(int val, QWidget *parent = nullptr);

public slots:
    void on_btn_close_clicked();

    void setProgressBarValue(int val);

signals:
    /**
     * @brief 点击取消按钮信号
     */
    void btnCancelClicked();

private:
    Ui::ProgressBarDlg ui{};
    int time = 0;
};
