#include "imagecheckpage.h"

ImageCheckPage::ImageCheckPage(QWidget *parent)
    : DefaultPage(parent)
{
    initUi();
}

void ImageCheckPage::initUi()
{
    ui.comboBox_s_project_id->addItems({"心电图", "超声科", "放射科"});
    ui.comboBox_s_project_id->setItemData(0, "XDT13149", Qt::UserRole + 1);
    ui.comboBox_s_project_id->setItemData(1, "CSK13159", Qt::UserRole + 1);
    ui.comboBox_s_project_id->setItemData(2, "FSK13169", Qt::UserRole + 1);

    ui.comboBox_s_project_id->setItemData(0, 90.5, Qt::UserRole + 2);
    ui.comboBox_s_project_id->setItemData(1, 87.5, Qt::UserRole + 2);
    ui.comboBox_s_project_id->setItemData(2, 77, Qt::UserRole + 2);
}
