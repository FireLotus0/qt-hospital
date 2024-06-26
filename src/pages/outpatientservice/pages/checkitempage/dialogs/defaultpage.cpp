#include "defaultpage.h"
#include <QListView>
#include <QDebug>
#include "appsetting.h"

DefaultPage::DefaultPage(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    initUi();
}

void DefaultPage::initUi()
{
    ui.comboBox_s_project_id->setView(new QListView);
    ui.edit_s_doctor_name->setText(CurDoctor::getInstance().name);
}

CheckProject DefaultPage::getContent()
{
    CheckProject pro;
    pro.s_project_id = ui.comboBox_s_project_id->currentData(Qt::UserRole + 1).toString();
    pro.s_price = ui.comboBox_s_project_id->currentData(Qt::UserRole + 2).toDouble();
    pro.s_num = ui.spinBox->value();
    pro.s_note = ui.textEdit->toPlainText();
    pro.s_total = pro.s_num * pro.s_price;
    pro.s_patient_id = CurPatient::getInstance().s_patient_id;
    pro.s_project_name = ui.comboBox_s_project_id->currentText();
    pro.s_project_name_f = ui.comboBox_s_project_id->currentText();
    pro.s_project_size = "测试";
    pro.s_doctor_name = CurDoctor::getInstance().name;
    return pro;
}
