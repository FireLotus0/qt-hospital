#include "searchdlg.h"
#include "pages/dialogs/datepick/datepickerpopup.h"
#include "utils/nethelp.h"
#include "pages/outpatientservice/recorddialog.h"

#include <QStyleOption>
#include <QPainter>
#include <QDateTime>
#include <QDebug>

#define CHECK_COND(edit, key, json) \
    if(!edit->text().isEmpty()) { \
        auto text = edit->text(); \
        json[#key] = text.replace("'","@"); }

SearchDlg::SearchDlg(QWidget *parent)
    : WindowFramelessWidget<QDialog>(parent)
{
    ui.setupUi(this);
    setMoveAreaWidget(ui.widget);

    initUi();
}

void SearchDlg::on_btn_date_clicked()
{
    auto dlg = new DatePickerPopup(QDateTime::currentDateTime());
    connect(dlg, &DatePickerPopup::onDateTimeChanged, this, [&](const QDateTime& date){
        ui.edit_s_make_date->setText(date.toString("yyyy-MM-dd"));
    });
    auto pos = findWidgetBottomGlobalPos(ui.btn_date);
    dlg->setGeometry(pos.x(), pos.y(), dlg->width(), dlg->height());
    dlg->show();
}

void SearchDlg::on_btn_close_clicked()
{
    close();
}

void SearchDlg::on_btn_clear_clicked()
{
    ui.edit_s_make_date->clear();
    ui.edit_s_patient_id->clear();
    ui.edit_s_doctor_name->clear();
    ui.edit_s_insurance_id->clear();
    ui.edit_s_patient_name->clear();
    ui.rbtn_boy->setChecked(false);
    ui.rbtn_girl->setChecked(false);
}

void SearchDlg::on_btn_query_clicked()
{
    QJsonObject json;

    CHECK_COND(ui.edit_s_make_date, s_make_date, json)
    CHECK_COND(ui.edit_s_patient_id, s_patient_id, json)
    CHECK_COND(ui.edit_s_doctor_name, s_doctor_name, json)
    CHECK_COND(ui.edit_s_insurance_id, s_insurance_id, json)
    CHECK_COND(ui.edit_s_patient_name, s_patient_name, json)
    if(ui.rbtn_boy->isChecked()) {
        json["s_patient_sex"] = "男";
    } else if(ui.rbtn_girl->isChecked()) {
        json["s_patient_sex"] = "女";
    }

    NetHelp::send("medical", false, json);
    connect(NetHelp::getThis(), GETSIG(medical), this, [&](const QByteArray& data){
       auto objList = NetHelp::parseResult(data);
       dataList.clear();
       for(auto& data : objList) {
           PatientInfo info;
           RecordDialog::loadDataHelp(info, data);
           dataList.push_back(info);
       }
       //添加数据到model
       auto model = ui.tableView->getModel();
       model->clear();
       initUi();
       int rowCount = dataList.size();
       for(int i = 0 ;i < rowCount; i++) {
           ui.tableView->insertModelData(QVariantList() << dataList[i].s_patient_id
               << dataList[i].s_patient_name << dataList[i].s_patient_sex
               << dataList[i].s_make_date << dataList[i].s_expense_source
               << dataList[i].s_insurance_id << dataList[i].s_doctor_name);
       }
    });
}

void SearchDlg::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p;
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SearchDlg::initUi()
{
    ui.tableView->setHorizontalHeaderLabels({"病人ID", "姓名", "性别", "制单日期", "费用来源", "医保应用号", "制单人"});
}

QPoint SearchDlg::findWidgetBottomGlobalPos(QPushButton *widget)
{
    QWidget* topWidget = widget->parentWidget();
    if(!topWidget) {
        return widget->pos();
    }
    QPoint pos;

    while(topWidget->parentWidget()) {
        pos += topWidget->pos();
        topWidget = topWidget->parentWidget();
    }
    pos += topWidget->pos();
    pos += {0, widget->parentWidget()->height()};
    return pos;
}
