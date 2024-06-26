#pragma once

#include <QDialog>
#include "utils/windowframelesshelper.h"
#include "ui_searchdlg.h"
#include "appsetting.h"
#include <QStandardItemModel>

class SearchDlg : public WindowFramelessWidget<QDialog>
{
    Q_OBJECT

public:
    explicit SearchDlg(QWidget* parent = nullptr);

public slots:
    void on_btn_date_clicked();

    void on_btn_close_clicked();

    void on_btn_clear_clicked();

    void on_btn_query_clicked();
protected:
    void paintEvent(QPaintEvent*)override;

private:
    void initUi();

    QPoint findWidgetBottomGlobalPos(QPushButton* widget);

private:
    Ui::SearchDlg ui{};
    QList<PatientInfo> dataList;
};
