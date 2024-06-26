#include "laboratorycheckpage.h"

LaboratoryCheckPage::LaboratoryCheckPage(QWidget *parent)
    : DefaultPage(parent)
{
    initUi();
}

void LaboratoryCheckPage::initUi()
{
    ui.comboBox_s_project_id->addItems({"实验室检查"});
    ui.comboBox_s_project_id->setItemData(0, "LABC9089", Qt::UserRole + 1);

    ui.comboBox_s_project_id->setItemData(0, 88, Qt::UserRole + 2);

}
