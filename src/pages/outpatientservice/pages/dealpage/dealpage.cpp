#include "dealpage.h"

#include "pages/dialogs/messagedlg/progressbardlg.h"
#include "utils/nethelp.h"
#include "pages/dialogs/messagedlg/messagedlg.h"
#include "utils/printhelp.h"
#include "appsetting.h"
#include "utils/nethelp.h"

DealPage::DealPage(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

void DealPage::on_btn_commit_hospital_clicked()
{
    if(CurPatient::getInstance().s_patient_id.isEmpty()) {
        MessageDlg::showDlg(MessageType::Hint_Error, "请先选择病人");
        return;
    }
    QJsonObject json;
    json["s_patient_id"] = CurPatient::getInstance().s_patient_id;
    json["s_patient_name"] = CurPatient::getInstance().s_patient_name;
    json["s_patient_sex"] = CurPatient::getInstance().s_patient_sex;
    json["s_patient_addr"] = CurPatient::getInstance().s_addr;
    json["s_work_unit"] =  ui.s_work_unit->text();
    json["s_work_phone"] = ui.s_work_phone->text();
    json["s_home_addr"] = ui.s_home_addr->text();
    json["s_home_phone"] = ui.s_home_phone->text();
    json["s_diagnose"] = ui.s_diagnose->text();
    json["s_family_name"] = ui.s_family_name->text();
    json["s_family_relation"] = ui.s_family_relation->text();
    json["s_family_unit"] = ui.s_family_unit->text();
    json["s_family_phone"] = ui.s_family_phone->text();
    json["s_family_addr"] = ui.s_family_addr->text();
    json["s_fee"] = ui.s_fee->text().toDouble();
    json["s_date"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    json["s_doctor"] =  CurDoctor::getInstance().name;
    json["s_department"] = CurDoctor::getInstance().department;
    json["s_in_department"] = ui.s_in_department->text();

    QJsonArray array;
    array.append(json);
    NetHelp::send("notify", false, QJsonObject(), array);
    connect(NetHelp::getThis(), GETSIG(notify), this, [&](const QByteArray& data){
           auto res = NetHelp::parseResult(data);
           if(res.isEmpty()) {
               MessageDlg::showDlg(MessageType::Hint_Error, "住院通知开具失败");
                return;
           }
           if(res[0]["result"].toBool()) {
               MessageDlg::showDlg(MessageType::Hint_Success, "住院通知开具成功");
           } else {
               MessageDlg::showDlg(MessageType::Hint_Error, "住院通知开具失败");
           }
       });
}

void DealPage::on_btn_commit_verify_clicked()
{
    if(CurPatient::getInstance().s_patient_id.isEmpty()) {
        MessageDlg::showDlg(MessageType::Hint_Error, "请先选择病人");
        return;
    }
    QJsonObject json;
    json["s_patient_id"] = CurPatient::getInstance().s_patient_id;
    json["s_patient_name"] = CurPatient::getInstance().s_patient_name;
    json["s_patient_sex"] = CurPatient::getInstance().s_patient_sex;
    json["s_age"] = ui.s_age->text().toInt();
    json["s_department"] =  CurDoctor::getInstance().department;
    json["s_first_diagnose"] = ui.s_first_diagnose->toPlainText();
    json["s_adviser"] = ui.s_adviser->toPlainText();
    json["s_last_modify_name"] = ui.s_last_modify_name->text();
    json["s_last_modify_date"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    json["s_doctor_name"] = CurDoctor::getInstance().name;

    QJsonArray array;
    array.append(json);
    NetHelp::send("prove", false, QJsonObject(), array);
    connect(NetHelp::getThis(), GETSIG(prove), this, [&](const QByteArray& data){
           auto res = NetHelp::parseResult(data);
           if(res.isEmpty()) {
               MessageDlg::showDlg(MessageType::Hint_Error, "诊断证明开具失败");
                return;
           }
           if(res[0]["result"].toBool()) {
               MessageDlg::showDlg(MessageType::Hint_Success, "诊断证明开具成功");
           } else {
               MessageDlg::showDlg(MessageType::Hint_Error, "诊断证明开具失败");
           }
       });
}

void DealPage::on_btn_print_hospital_clicked()
{
    PrintHelper::printWidget(ui.widget_notify);
}

void DealPage::on_btn_print_verify_clicked()
{
    PrintHelper::printWidget(ui.widget_cert);
}



