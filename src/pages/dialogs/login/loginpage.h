#pragma once

#include "ui_loginpage.h"
#include "utils/inputtester.h"
#include "utils/windowframelesshelper.h"

#include <qpainter.h>
#include <qevent.h>
#include <qdialog.h>
#include <appsetting.h>

class LoginPage : public WindowFramelessWidget<QDialog>
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

signals:
    void userLogined(const QString& user);

    void userQuit();

    void connectError();

private:
    Ui::LoginPage ui{};

private:
    /**
     * @brief 空值校验
     * @param condition 是否为空值，true：空值
     * @param type 当前输入控件类型：用户名输入控件，密码输入控件
     * @param input 当前输入控件
     * @return 校验是否通过，true：非空值
     */
    bool emptyCheck(bool condition, const QString& content, QWidget* input);

private slots:
    /**
     * @brief 点击登录
     */
    void on_btn_login_clicked();

    /**
     * @brief 点击退出
     */
    void on_btn_account_error_right_clicked();
};
