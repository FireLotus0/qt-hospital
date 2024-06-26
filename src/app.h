#pragma once

#include "utils/windowframelesshelper.h"
#include <QWidget>
#include  <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class App; }
QT_END_NAMESPACE

class App : public WindowFramelessWidget<QWidget>
{
    Q_OBJECT

public:
    App(QWidget *parent = nullptr);
    ~App();


    void setUserName(const QString& name);

public slots:
    void on_btn_close_clicked();

protected:
    QSize sizeHint() const override;

private:
    void initUi();

private slots:
    void switchPage(int index);

private:
    Ui::App *ui;
    QTimer* timer;
};

