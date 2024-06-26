#include "app.h"
#include "./ui_app.h"
#include "pages/outpatientservice/outpatientservice.h"
#include "pages/doctor/mainpage.h"

#include <QDateTime>
#include <QListView>
#include <QComboBox>
#include <QDebug>

App::App(QWidget *parent)
    : WindowFramelessWidget(parent)
    , ui(new Ui::App)
{
    ui->setupUi(this);
    resize(1900, 1000);
    setMoveAreaWidget(ui->widget_title);
    initUi();
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, [&]() {
        ui->label_time->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    });
    timer->start();

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(switchPage(int)));
}

App::~App()
{
    delete ui;
}

void App::setUserName(const QString &name)
{
    ui->label_user->setText(name);
}

QSize App::sizeHint() const
{
    return {1900, 900};
}

void App::on_btn_close_clicked() {
    close();
}

void App::initUi()
{
    ui->comboBox->setView(new QListView);

    ui->stackedWidget->addWidget(new OutpatientService(this));
    ui->stackedWidget->addWidget(new MainPage(this));
    ui->stackedWidget->setCurrentIndex(0);
}

void App::switchPage(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

