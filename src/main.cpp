#include "app.h"
#include "pages/dialogs/login/loginpage.h"
#include "appsetting.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto dlg = new LoginPage;
    App w;
    QObject::connect(dlg, &LoginPage::userLogined, [&](const QString& user){
        w.setUserName(user);
    });
    QObject::connect(dlg, &LoginPage::userQuit, [&](){
        exit(0);
    });

   if(dlg->exec() == QDialog::Accepted) {
       w.setWindowState(Qt::WindowMaximized);
       w.show();
   };
    return a.exec();
}
