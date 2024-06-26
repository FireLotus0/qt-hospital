#include "recorddialog.h"
#include "pages/dialogs/search/searchdlg.h"
#include  <qpainter.h>
#include "utils/nethelp.h"
#include <QDebug>

RecordDialog::RecordDialog(QWidget *parent)
    : QWidget(parent)
{
    initTableProperty();
    emit(ui.btn_all->clicked());

    connect(ui.tableView, &QTableView::clicked, this, [&](const QModelIndex& index){
        if(index.isValid()) {
            //加载数据
            loadData(curTag);
            ui.tableView->setModel(model);
            CurPatient::getInstance() = dataList[index.row()];
            emit itemSelected();
        }
    });

}

void RecordDialog::clickToSwitchPage() {
    auto* obj = qobject_cast<QPushButton*>(sender());
    updateButtonCheckStatus(obj);
    //加载数据
    loadData(obj->property("record").value<RecordType>());
    ui.tableView->setModel(model);
}

//点击查询
void RecordDialog::on_btn_find_clicked()
{
    auto dlg = new SearchDlg();
    dlg->show();
}

void RecordDialog::updateButtonCheckStatus(QPushButton* btn) {
    ui.btn_hurry->setChecked(btn == ui.btn_hurry);
    ui.btn_all->setChecked(btn == ui.btn_all);
    ui.btn_health->setChecked(btn == ui.btn_health);
    ui.btn_common->setChecked(btn == ui.btn_common);
}

void RecordDialog::loadData(RecordType tag) {
    //根据标签从数据库加载数据
    QJsonObject json;
    json["s_doctor_name"] = CurDoctor::getInstance().name;
    switch(tag) {
        case All_Record: {
            json["s_type"] = 0;
            curTag = All_Record;
            break;
        }
        case Hurry_Record: {
            json["s_type"] = 1;
            curTag = Hurry_Record;
            break;
        }
        case Common_Record:{
            json["s_type"] = 2;
            curTag = Common_Record;
            break;
        }
        case Health_Record:{
            json["s_type"] = 3;
            curTag = Health_Record;
            break;
        }
    }
    NetHelp::send("medical", false, json);
    connect(NetHelp::getThis(), GETSIG(medical), this, [&](const QByteArray& data){
       auto objList = NetHelp::parseResult(data);
       dataList.clear();
       for(auto& data : objList) {
           PatientInfo info;
           loadDataHelp(info, data);
           dataList.push_back(info);
       }
       //添加数据到model
       model->clear();
       model->setRowCount(dataList.size());
       int rowCount = model->rowCount();
       for(int i = 0 ;i < rowCount; i++) {
           model->setItem(i, 0, new QStandardItem(dataList[i].s_patient_name));
           model->setItem(i, 1, new QStandardItem(dataList[i].s_patient_sex));
           model->setItem(i, 2, new QStandardItem(QString::number(dataList[i].s_age)));
       }
    });
}

void deal(){}

void RecordDialog::initTableProperty() {
    ui.setupUi(this);
    model = new QStandardItemModel(this);
    ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setWindowFlags(windowFlags() | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground);

    ui.btn_all->setProperty("record", RecordType::All_Record);
    ui.btn_hurry->setProperty("record", RecordType::Hurry_Record);
    ui.btn_common->setProperty("record", RecordType::Common_Record);
    ui.btn_health->setProperty("record", RecordType::Health_Record);

    connect(ui.btn_all, &QPushButton::clicked, this, &RecordDialog::clickToSwitchPage);
    connect(ui.btn_hurry, &QPushButton::clicked, this, &RecordDialog::clickToSwitchPage);
    connect(ui.btn_common, &QPushButton::clicked, this, &RecordDialog::clickToSwitchPage);
    connect(ui.btn_health, &QPushButton::clicked, this, &RecordDialog::clickToSwitchPage);
}

void RecordDialog::loadDataHelp(PatientInfo &info, QJsonObject &data)
{
    info.s_age = data.value("s_age").toInt();
    info.s_job = data.value("s_job").toString();
    info.s_addr = data.value("s_addr").toString();
    info.s_date = data.value("s_date").toString();
    info.s_deal = data.value("s_deal").toString();
    info.s_type = data.value("s_type").toInt();
    info.s_phone = data.value("s_phone").toString();
    info.s_id_type = data.value("s_id_type").toString();
    info.s_doctor_id = data.value("s_doctor_id").toInt();
    info.s_main_suit = data.value("s_main_suit").toString();
    info.s_make_date = data.value("s_make_date").toString();
    info.s_body_check = data.value("s_body_check").toString();
    info.s_department = data.value("s_department").toString();
    info.s_help_check = data.value("s_help_check").toString();
    info.s_patient_id = data.value("s_patient_id").toString();
    info.s_doctor_name = data.value("s_doctor_name").toString();
    info.s_patient_sex = data.value("s_patient_sex").toString();
    info.s_insurance_id = data.value("s_insurance_id").toString();
    info.s_patient_name = data.value("s_patient_name").toString();
    info.s_blood_pressure = data.value("s_blood_pressure").toString();
    info.s_expense_source = data.value("s_expense_source").toString();
    info.s_first_diagnose = data.value("s_first_diagnose").toString();
    info.s_present_illness = data.value("s_present_illness").toString();
    info.s_meal_blood_glucose = data.value("s_meal_blood_glucose").toString();
    info.s_empty_blood_glucose = data.value("s_empty_blood_glucose").toString();
}
