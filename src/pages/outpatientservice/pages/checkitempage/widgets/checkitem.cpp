#include "checkitem.h"
#include <QDateTime>
CheckItem::CheckItem(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
}

void CheckItem::setContent(QStringList data)
{
    ui.lineedit_num->setText(data[0]);
    ui.lineedit_user->setText(data[1]);
    ui.lineedit_date->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui.lineedit_project->setText(data[2]);
}
