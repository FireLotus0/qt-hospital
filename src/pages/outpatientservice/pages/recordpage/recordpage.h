#pragma once
#include "ui_recordpage.h"
#include "pages/outpatientservice/recorddialog.h"

#include <QWidget>
#include <QTextBrowser>

class RecordPage : public QWidget
{
    Q_OBJECT

public:
    RecordPage(QWidget* parent = nullptr);

    void updateData();

private:
    void initSigSlots();

    void loadLineEdit(QLineEdit* edit, QString* str);

    void loadLineEdit(QLineEdit* edit, int* data);

    void initSigLineEdit(QLineEdit* edit, QString* str);

    void initSigLineEdit(QLineEdit* edit, int* data);

    void initData();

    void commitHelp();

private slots:

    void on_btn_print_clicked();

    void on_btn_pdf_clicked();

private:
    Ui::RecordPage ui;
};
