#include "checkitempage.h"
#include "utils/printhelp.h"

#include "dialogs/checkselectdlg.h"
#include "utils/nethelp.h"
#include "pages/dialogs/messagedlg/messagedlg.h"

#include <QJsonObject>

CheckItemPage::CheckItemPage(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    iniUi();
    initSigSlots();
}

void CheckItemPage::on_btn_add_clicked()
{
    if(ui.edit_s_department->text().isEmpty()) {
        MessageDlg::showDlg(MessageType::Hint_Error, "请先填写科室！");
        return;
    }
    if(ui.edit_s_check_part->text().isEmpty()) {
        MessageDlg::showDlg(MessageType::Hint_Error, "请先填写部位！");
        return;
    }
    if(ui.edit_s_goal->text().isEmpty()) {
        MessageDlg::showDlg(MessageType::Hint_Error, "请先填写检查目的！");
        return;
    }

    auto dlg = new CheckSelectDlg;
    connect(dlg, &CheckSelectDlg::confirmed, this, [&](CheckProject pro){
        auto item = new CheckItem();
        item->setContent(QStringList() << pro.s_project_id <<
                         pro.s_doctor_name << pro.s_project_name);
        dataItem << item;
        pro.s_check_part = ui.edit_s_check_part->text();
        pro.s_goal = ui.edit_s_goal->text();
        pro.s_department = ui.edit_s_department->text();
        dataList << pro;
        ui.horizontalLayout_tag->insertWidget(ui.horizontalLayout_tag->count()-1,item, 0, Qt::AlignLeft);
        ui.tableView->insertModelData({pro.s_project_id, pro.s_project_name, pro.s_project_name,
                                       pro.s_project_size, pro.s_price, pro.s_num, pro.s_total});

    });
    dlg->show();
}

void CheckItemPage::on_btn_delete_clicked()
{
    auto index = ui.tableView->currentIndex();
    if(index.isValid()) {
        qDeleteAll(ui.tableView->getModel()->takeRow(index.row()));
        auto widget = dataItem[index.row()];
        ui.horizontalLayout_tag->removeWidget(widget);
        dataItem.removeAt(index.row());
        delete widget;
    }
}

void CheckItemPage::initSigSlots()
{
}

void CheckItemPage::on_btn_generate_clicked()
{

}

void CheckItemPage::on_btn_print_clicked()
{
    PrintHelper::printWidget(ui.tableView);
}

void CheckItemPage::on_btn_pdf_clicked()
{
    PrintHelper::toPdf(ui.tableView);

}

void CheckItemPage::on_btn_commit_clicked()
{
    if(dataList.size() == 0) {
        return;
    }
    QJsonArray array;
    for(auto& data : dataList) {
        QJsonObject obj;
        obj["s_project_id"] = data.s_project_id;
        obj["s_patient_id"] = data.s_patient_id;
        obj["s_note"] = data.s_note;
        obj["s_doctor_name"] = data.s_doctor_name;
        obj["s_department"] = data.s_department;
        obj["s_check_part"] = data.s_check_part;
        obj["s_goal"] = data.s_goal;
        obj["s_project_name"] = data.s_project_name;
        obj["s_project_name_f"] = data.s_project_name_f;
        obj["s_project_size"] = data.s_project_size;
        obj["s_price"] = data.s_price;
        obj["s_num"] = data.s_num;
        obj["s_total"] = data.s_total;
        array.append(obj);
    }
    NetHelp::send("commitCheck", false, QJsonObject(), array);
    connect(NetHelp::getThis(), GETSIG(commitCheck), this, [&](const QByteArray& data){
       auto res = NetHelp::parseResult(data);
       if(res[0]["result"].toBool()) {
           MessageDlg::showDlg(MessageType::Hint_Success, "检查单提交成功");
       } else {
           MessageDlg::showDlg(MessageType::Hint_Error, "检查单提交失败");
       }
    });
}

void CheckItemPage::iniUi()
{
    ui.horizontalLayout_tag->addStretch();
    ui.tableView->setHorizontalHeaderLabels({"项目编码", "项目名称", "收费项目名称", "项目规格", "价格", "数量", "金额"});
}
