#include "outpatientservice.h"

#include "pages/checkitempage/checkitempage.h"
#include "pages/recordpage/recordpage.h"
#include "pages/medicinepage/medicinepage.h"
#include "pages/dealpage/dealpage.h"

OutpatientService::OutpatientService(QWidget *parent)
  :  QWidget(parent)
{
    ui.setupUi(this);

    iniUi();
    connect(ui.recordWidget, &RecordDialog::itemSelected, this, [&]{
        //当前界面是否为电子病历
        if(ui.tabWidget->currentIndex() == 0) {
            auto page = dynamic_cast<RecordPage*>(ui.tabWidget->widget(0));
            if(page) {
                page->updateData();
            }
        }
    });
}

void OutpatientService::iniUi()
{
    ui.tabWidget->setContentsMargins(0,0,0,0);
    ui.tabWidget->addTab(new RecordPage(this), "电子病历");
    ui.tabWidget->addTab(new CheckItemPage(this), "检查单");
    ui.tabWidget->addTab(new MedicinePage(this), "处方药");
    ui.tabWidget->addTab(new DealPage(this), "处置");
}

void OutpatientService::updatePatient()
{

}
