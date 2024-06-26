#include "bodycheckpage.h"

BodyCheckPage::BodyCheckPage(QWidget *parent)
    : DefaultPage(parent)
{
    initUi();
}

void BodyCheckPage::initUi()
{
    ui.comboBox_s_project_id->addItems({"一般检查", "内科检查"});
    ui.comboBox_s_project_id->setItemData(0, "YBJC0010", Qt::UserRole + 1);
    ui.comboBox_s_project_id->setItemData(1, "NKJC0020", Qt::UserRole + 1);

    ui.comboBox_s_project_id->setItemData(0, 40, Qt::UserRole + 2);
    ui.comboBox_s_project_id->setItemData(1, 80, Qt::UserRole + 2);
}
