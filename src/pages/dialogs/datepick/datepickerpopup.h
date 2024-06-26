#pragma once

#include <QDateTime>
#include <QStandardItemModel>

#include "ui_datepickerpopup.h"

/*
 * 功能：日期时间选择器（悬浮框）
 */

class DatePickerPopup : public QWidget
{
    Q_OBJECT
public:
    explicit DatePickerPopup(QDateTime  time, QWidget* parent = nullptr);

signals:
    void onDateTimeChanged(const QDateTime& curTime);

private:
    void initTableView();
    void initTableViewData();

    void selectCurrentDate();
    void setLabelText();

private slots:
    void on_btn_today_clicked();

    void on_btn_left_year_clicked();
    void on_btn_left_month_clicked();
    void on_btn_right_year_clicked();
    void on_btn_right_month_clicked();

private:
    Ui::DatePickerPopup ui;

    QStandardItemModel* dateModel;
    QDateTime currentDateTime;
};
