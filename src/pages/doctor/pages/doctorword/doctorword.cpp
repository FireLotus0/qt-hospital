#include "doctorword.h"

DoctorWords::DoctorWords(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    ui.tableView->setHorizontalHeaderLabels({"开医嘱时间", "执行起始时间", "开医嘱医生",
                                            "校对护士", "长期医嘱", "给药途径", "执行频率",
                                            "停止时间", "停止医嘱医生"});
}
