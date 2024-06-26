#include "patientselect.h"

#include "pages/dialogs/datepick/datepickerpopup.h"
#include "utils/findposhelper.h"

PatientSelect::PatientSelect(QWidget* parent)
    : QWidget(parent) {

    ui.setupUi(this);
    initTable();
}

void PatientSelect::initTable() {
    ui.tableView->setHorizontalHeaderLabels({"挂号单号", "病人ID", "姓名", "性别"});
}

void PatientSelect::on_btn_date_start_clicked()
{
    auto dlg = new DatePickerPopup(QDateTime::currentDateTime());
    connect(dlg, &DatePickerPopup::onDateTimeChanged, this, [&](const QDateTime& date){
        ui.lineedit_date_start->setText(date.toString("yyyy-MM-dd"));
    });
    auto pos = FindPosHelper::findParentWidgetBottomGlobalPos(ui.btn_date_start);
    dlg->setGeometry(pos.x(), pos.y(), dlg->width(), dlg->height());
    dlg->show();
}

void PatientSelect::on_btn_date_end_clicked()
{
    auto dlg = new DatePickerPopup(QDateTime::currentDateTime());
    connect(dlg, &DatePickerPopup::onDateTimeChanged, this, [&](const QDateTime& date){
        ui.lineedit_date_end->setText(date.toString("yyyy-MM-dd"));
    });
    auto pos = FindPosHelper::findParentWidgetBottomGlobalPos(ui.btn_date_end);
    dlg->setGeometry(pos.x(), pos.y(), dlg->width(), dlg->height());
    dlg->show();
}
