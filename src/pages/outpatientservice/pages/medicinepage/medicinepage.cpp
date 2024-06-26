#include "medicinepage.h"
#include "pages/dialogs/messagedlg/messagedlg.h"
#include "utils/nethelp.h"

#include <QListView>
#include <QDateTime>
#include <qdebug.h>

MedicinePage::MedicinePage(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    iniUi();
    lastWidget = nullptr;
    initSheet();
    initSigSlots();
}

MedicinePage::~MedicinePage()
{
    qDeleteAll(medicineList);
}

void MedicinePage::on_btn_query_clicked()
{
    QJsonObject json;
    json["s_pharmacy"] = ui.comboBox_pharmacy->currentText();
    json["s_prescription_type"] = ui.comboBox_type->currentIndex();
    json["s_skin_test"] = ui.comboBox_res->currentIndex();
    json["s_medical_type"] = ui.comboBox_medicine_type->currentIndex();
    if(!ui.lineEdit_name->text().isEmpty()) {
        json["s_name"] = ui.lineEdit_name->text().replace("'","@");
    }
    NetHelp::send("medicine", false, json);
    connect(NetHelp::getThis(), GETSIG(medicine), this, [&](const QByteArray& data){
        parseQuery(NetHelp::parseResult(data));
    });
}

void MedicinePage::iniUi()
{
    ui.comboBox_res->setView(new QListView);
    ui.comboBox_type->setView(new QListView);
    ui.comboBox_pharmacy->setView(new QListView);
    ui.comboBox_medicine_type->setView(new QListView);

    ui.table_medicine->setHorizontalHeaderLabels({"药品名称", "药品编号", "条码",
         "规格", "单位", "生产厂商", "批准文号", "价格", "备注"});
    ui.verticalLayout_medicine->addStretch();
}

void MedicinePage::parseQuery(const QList<QJsonObject> &datas)
{
    queryList.clear();
    for(auto& data : datas) {
        Medicine medicine;
        medicine.s_name = data.value("s_name").toString();
        medicine.s_bar_code = data.value("s_bar_code").toString();
        medicine.s_size = data.value("s_size").toString();
        medicine.s_unit = data.value("s_unit").toString();
        medicine.s_manufacturer = data.value("s_manufacturer").toString();
        medicine.s_approval_number = data.value("s_approval_number").toString();
        medicine.s_price = data.value("s_price").toDouble();
        medicine.s_pharmacy = data.value("s_pharmacy").toString();
        medicine.s_tabu = data.value("s_tabu").toString();
        medicine.s_adaptation_disease = data.value("s_adaptation_disease").toString();
        medicine.s_adverse_reaction = data.value("s_adverse_reaction").toString();
        medicine.s_special_note = data.value("s_special_note").toString();
        medicine.s_note = data.value("s_note").toString();
        medicine.s_medicine_id = data.value("s_medicine_id").toString();
        medicine.s_prescription_type = data.value("s_prescription_type").toInt();
        medicine.s_skin_test = data.value("s_skin_test").toInt();
        medicine.s_medical_type = data.value("s_medical_type").toInt();
        queryList << medicine;
        qDebug() << "medicine query:" << data;
    }
    QVariantList tmp;
    //{"药品名称", "药品编号", "条码","规格", "单位", "生产厂商", "批准文号", "价格", "备注"});
    for(auto& medicine : queryList) {
        auto note = medicine.s_note.isEmpty() ? "无" : medicine.s_note;
        tmp << medicine.s_name << medicine.s_medicine_id << medicine.s_bar_code
            << medicine.s_size << medicine.s_unit << medicine.s_manufacturer <<
               medicine.s_approval_number << medicine.s_price
            <<  note;
    }
    clearTable();
    if(queryList.empty()) {
        return;
    }
    ui.table_medicine->insertModelData(tmp);

}

void MedicinePage::clearTable()
{
    auto model = ui.table_medicine->getModel();
    model->clear();
    ui.table_medicine->setHorizontalHeaderLabels({"药品名称", "药品编号", "条码",
                                                  "规格", "单位", "生产厂商", "批准文号", "价格", "备注"});
}

void MedicinePage::initSigSlots()
{
    //添加药品
    connect(ui.table_medicine, &QTableView::doubleClicked, this, [&](const QModelIndex &index){
        if(index.isValid()) {
            auto name = index.model()->data(index.model()->index(index.row(), 0)).toString();
            auto dlg = MessageDlg::showDlg(MessageType::Hint_Help, "是否添加药品：" + name);

            connect(dlg, &MessageDlg::accepted, this, [&,index](){
                int id = medicineList.count();
                auto medicine = new MedicineWidget(id);
                medicineList[id] = medicine;
                dataList[id] = queryList[index.row()];
                auto text = QStringList{dataList[id].s_name,
                        QString::number(dataList[id].s_price),
                        dataList[id].s_special_note};
                medicine->setText(text);
                ui.verticalLayout_medicine->insertWidget(ui.verticalLayout_medicine->count() - 1,
                medicine, 0, Qt::AlignTop);

                connect(medicine, &MedicineWidget::deleteMedicine, this, [&](int id){
                    auto widget = medicineList[id];
                    if(lastWidget == widget) {
                        lastWidget = nullptr;
                    }
                    ui.verticalLayout_medicine->removeWidget(widget);
                    dataList.remove(id);
                    medicineList.remove(id);
                    delete widget;
                });
                connect(medicine, &MedicineWidget::widgetClicked, this, [&](MedicineWidget* cur){
                    if(lastWidget) {
                        lastWidget->setStyleSheet(normalSheet);
                    }
                    cur->setStyleSheet(selectedSheet);
                    lastWidget = cur;
                    setInfoText(cur->getId());
                });
            });
        }
    });
}

void MedicinePage::updateWidget(MedicineWidget *cur)
{

}

void MedicinePage::initSheet()
{
  normalSheet = "#MedicineWidget{ \
          border:1px solid #77b5fe; \
          background-color: #e8ffe8; \
          } \
          QWidget{ \
          background:transparent; \
          border:none; \
          } \
          QLabel{ \
          color:#1a1a1a; \
          font-size:16px; \
          line-height:24px; \
          } \
          QLineEdit{ \
          color:#1a1a1a; \
          font-size:16px; \
          line-height:24px; \
          padding-left:8px; \
          border:none; \
          border-bottom:1px solid #1a1a1a; \
          }";
  selectedSheet = "#MedicineWidget{ \
          border:1px solid #77b5fe; \
          background-color: #a8e6cf; \
          } \
          QWidget{ \
          background:transparent; \
          border:none; \
          } \
          QLabel{ \
          color:#f20c00; \
          font-size:16px; \
          line-height:24px; \
          } \
          QLineEdit{ \
          color:#f20c00; \
          font-size:16px; \
          line-height:24px; \
          padding-left:8px; \
          border:none; \
          border-bottom:1px solid #f20c00; \
          }";
}

void MedicinePage::setInfoText(int id)
{
    if(!dataList.contains(id)) {
        qDebug() << "has no id:" << id;
        return;
    }
    auto medicine = dataList.value(id);
    ui.text_s_note->setText(medicine.s_note);
    ui.text_s_adverse->setText(medicine.s_adverse_reaction);
    ui.text_s_tabu->setText(medicine.s_tabu);
    ui.text_s_adaptation->setText(medicine.s_adaptation_disease);

}

void MedicinePage::on_btn_commit_clicked()
{
    if(CurPatient::getInstance().s_patient_id.isEmpty()) {
        MessageDlg::showDlg(MessageType::Hint_Error, "请先选择病人");
        return;
    }
    QString prescription;
    double val = 0;
    for(const auto& data : dataList) {
        prescription += data.s_name + "; ";
        val += data.s_price;
    }
    QJsonObject json;
    json["s_patient_id"] = CurPatient::getInstance().s_patient_id;
    json["s_patient_name"] = CurPatient::getInstance().s_patient_name;
    json["s_time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    json["s_cost"] = val;
    json["s_prescription"] = prescription;
    json["s_doctor_id"] = CurDoctor::getInstance().id;
    json["s_doctor_name"] = CurDoctor::getInstance().name;
    QJsonArray array;
    array.append(json);
    NetHelp::send("prescription", false, QJsonObject(), array);
    connect(NetHelp::getThis(), GETSIG(prescription), this, [&](const QByteArray& data){
           auto res = NetHelp::parseResult(data);
           if(res.isEmpty()) {
               MessageDlg::showDlg(MessageType::Hint_Error, "处方开具失败");
                return;
           }
           if(res[0]["result"].toBool()) {
               MessageDlg::showDlg(MessageType::Hint_Success, "处方开具成功");
           } else {
               MessageDlg::showDlg(MessageType::Hint_Error, "处方开具失败");
           }
       });
}
