#include "loginpage.h"
#include "widgets/messagehint/messagehint.h"
#include "utils/nethelp.h"
#include <QPainter>
#include <QStyleOption>

LoginPage::LoginPage(QWidget *parent)
        : WindowFramelessWidget<QDialog>(parent)
{
    ui.setupUi(this);

    ui.widget_error_hint->setVisible(false);

    setMoveAreaWidget(ui.widget_title);

    connect(NetHelp::getThis(), GETSIG(login), this, [&](const QByteArray& data){
        auto res = NetHelp::parseResult(data);
        if(!res.isEmpty()) {
            auto& doc =  CurDoctor::getInstance();
            doc.id = res[0]["s_id"].toInt();
            doc.name = res[0]["s_name"].toString();
            doc.passwd = res[0]["s_passwd"].toString();
            doc.department = res[0]["s_department"].toString();
            //qDebug() << "doc"<<CurDoctor::getInstance().name;
        } else {
            ui.label_info->setText("服务器连接错误");
        }
    });

    connect(ui.btn_quit, &QPushButton::clicked, this, &LoginPage::userQuit);

    connect(ui.lineedit_passwd, &QLineEdit::returnPressed, this,
            [&]{ ui.btn_login->clicked();});
}

void LoginPage::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void LoginPage::on_btn_login_clicked() {
    InputTester::doTest([&](const QString& user, const QString& passwd){
            //校验空值
            auto isUserOk = emptyCheck(user.isEmpty(), "请输入用户名", ui.widget_user);
            auto isPasswdOk = emptyCheck(passwd.isEmpty(), "请输入密码", ui.widget_passwd);
            //空值，不做后续处理
            if(!isUserOk || !isPasswdOk) {
                return;
            }
            //检验用户名，密码正确性
            QJsonObject json;
            json["user"] = user;
            json["passwd"] = passwd;
            NetHelp::send("login", true, json);
            if(CurDoctor::getInstance().id != -1 && CurDoctor::getInstance().name == user) {
                userLogined(CurDoctor::getInstance().name);
                accept();
            } else {
                ui.widget_error_hint->setVisible(true);
            }
        }, ui.lineedit_user->text(), ui.lineedit_passwd->text());
}

bool LoginPage::emptyCheck(bool condition, const QString& content, QWidget* input) {
    if(condition) {
        auto hint = MessageHint::showMessage(content);

        //控件位置
        auto startX = this->pos().x() + input->pos().x() + 132;
        auto startY = this->pos().y() + input->pos().y() + 19;
        //移动控件
        hint->setGeometry(startX, startY, hint->width(), hint->height());
        return false;
    }
    return true;
}

void LoginPage::on_btn_account_error_right_clicked() {
    this->reject();
}

