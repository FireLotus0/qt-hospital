#include "recordpage.h"
#include "utils/printhelp.h"
#include "utils/nethelp.h"
#include "pages/dialogs/messagedlg/messagedlg.h"
#include "appsetting.h"

#include <QJsonObject>

RecordPage::RecordPage(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    initSigSlots();

    initData();
}

void RecordPage::initSigSlots()
{
    connect(ui.btn_commit, &QPushButton::clicked, this, [&]{
      commitHelp();
    });
}

void RecordPage::loadLineEdit(QLineEdit* edit, QString* str)
{
    //qDebug() << "loadLineEdit : " << *str;
    edit->setText(*str);
}

void RecordPage::loadLineEdit(QLineEdit *edit, int *data)
{
    edit->setText(QString::number(*data));
}

void RecordPage::initSigLineEdit(QLineEdit *edit, QString *str)
{
    connect(edit, &QLineEdit::editingFinished, this, [=]{
        *str = edit->text();

    });
}

void RecordPage::initSigLineEdit(QLineEdit *edit, int *data)
{
    connect(edit, &QLineEdit::editingFinished, this, [=]{
        bool ok = false;
        auto age = edit->text().toInt(&ok);
        if(ok) {
            *data = age;
        }
    });
}

void RecordPage::updateData()
{
    auto& data = CurPatient::getInstance();
    loadLineEdit(ui.edit_s_age, &data.s_age);
    loadLineEdit(ui.edit_s_patient_name, &data.s_patient_name);
    loadLineEdit(ui.edit_s_addr, &data.s_addr);
    loadLineEdit(ui.edit_s_phone, &data.s_phone);
    loadLineEdit(ui.edit_s_id_type, &data.s_id_type);
    loadLineEdit(ui.edit_s_date, &data.s_date);
    loadLineEdit(ui.edit_s_job, &data.s_job);
    loadLineEdit(ui.edit_s_main_suit, &data.s_main_suit);
    loadLineEdit(ui.edit_s_blood_pressure, &data.s_blood_pressure);
    loadLineEdit(ui.edit_s_empty_blood_glucose, &data.s_empty_blood_glucose);
    loadLineEdit(ui.edit_s_meal_blood_glucose, &data.s_meal_blood_glucose);
    loadLineEdit(ui.edit_s_first_diagnose, &data.s_first_diagnose);
    loadLineEdit(ui.edit_s_make_date, &data.s_make_date);
    loadLineEdit(ui.edit_s_doctor_name, &data.s_doctor_name);
    loadLineEdit(ui.edit_s_department, &data.s_department);

    ui.textEdit_s_present_illness->setText(data.s_present_illness);
    ui.textEdit_s_body_check->setText(data.s_body_check);
    ui.textEdit_s_help_check->setText(data.s_help_check);
    ui.textEdit_s_deal->setText(data.s_deal);
}

void RecordPage::initData()
{
    auto& data = CurPatient::getInstance();
    initSigLineEdit(ui.edit_s_age, &data.s_age);
    initSigLineEdit(ui.edit_s_patient_name, &data.s_patient_name);
    initSigLineEdit(ui.edit_s_addr, &data.s_addr);
    initSigLineEdit(ui.edit_s_phone, &data.s_phone);
    initSigLineEdit(ui.edit_s_job, &data.s_job);
    initSigLineEdit(ui.edit_s_id_type, &data.s_id_type);
    initSigLineEdit(ui.edit_s_date, &data.s_date);
    initSigLineEdit(ui.edit_s_main_suit, &data.s_main_suit);
    initSigLineEdit(ui.textEdit_s_present_illness, &data.s_present_illness);
    initSigLineEdit(ui.textEdit_s_body_check, &data.s_body_check);
    initSigLineEdit(ui.edit_s_blood_pressure, &data.s_blood_pressure);
    initSigLineEdit(ui.edit_s_empty_blood_glucose, &data.s_empty_blood_glucose);
    initSigLineEdit(ui.edit_s_meal_blood_glucose, &data.s_meal_blood_glucose);
    initSigLineEdit(ui.edit_s_first_diagnose, &data.s_first_diagnose);
    initSigLineEdit(ui.textEdit_s_help_check, &data.s_help_check);
    initSigLineEdit(ui.textEdit_s_deal, &data.s_deal);
}

void RecordPage::on_btn_print_clicked()
{
    PrintHelper::printWidget(ui.widget_info);
}

void RecordPage::on_btn_pdf_clicked()
{
    PrintHelper::toPdf(ui.widget_info);
}

void RecordPage::commitHelp()
{
    QJsonObject json;
    auto& data = CurPatient::getInstance();
    json["s_doctor_id"] = data.s_doctor_id;
    json["s_type"] = data.s_type;
    json["s_age"] = data.s_age;
    json["operation"] = "update";
    json["s_patient_id"] = data.s_patient_id;
    json["s_expense_source"] = data.s_expense_source;
    json["s_insurance_id"] = data.s_insurance_id;
    json["s_patient_name"] = data.s_patient_name;
    json["s_patient_sex"] = data.s_patient_sex;
    json["s_addr"] = data.s_addr;
    json["s_phone"] = data.s_phone;
    json["s_job"] = data.s_job;
    json["s_id_type"] = data.s_id_type;
    json["s_date"] = data.s_date;
    json["s_main_suit"] = data.s_main_suit;
    json["s_present_illness"] = data.s_present_illness;
    json["s_body_check"] = data.s_body_check;
    json["s_blood_pressure"] = data.s_blood_pressure;
    json["s_empty_blood_glucose"] = data.s_empty_blood_glucose;
    json["s_meal_blood_glucose"] = data.s_meal_blood_glucose;
    json["s_help_check"] = data.s_help_check;
    json["s_first_diagnose"] = data.s_first_diagnose;
    json["s_deal"] = data.s_deal;
    json["s_doctor_name"] = data.s_doctor_name;
    json["s_make_date"] = data.s_make_date;
    json["s_department"] = data.s_department;
    // "提交电子病历";
     NetHelp::send("modifyMedical", false, json);
     connect(NetHelp::getThis(), GETSIG(modifyMedical), this, [&](const QByteArray& data){
            auto res = NetHelp::parseResult(data);
            if(res[0]["result"].toBool()) {
                MessageDlg::showDlg(MessageType::Hint_Success, "提交成功");
            } else {
                MessageDlg::showDlg(MessageType::Hint_Error, "提交失败");
            }
        });
     updateData();
}
