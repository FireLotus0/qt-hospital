#include "othercheckpage.h"

OtherCheckPage::OtherCheckPage(QWidget *parent)
    : DefaultPage(parent)
{
    initUi();
}

void OtherCheckPage::initUi()
{
    ui.comboBox_s_project_id->addItems({"其他检查"});
    ui.comboBox_s_project_id->setItemData(0, "OTHE3149", Qt::UserRole + 1);

    ui.comboBox_s_project_id->setItemData(0, 66, Qt::UserRole + 2);

}
