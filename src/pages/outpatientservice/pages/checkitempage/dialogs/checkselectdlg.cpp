#include "checkselectdlg.h"
#include "bodycheckpage.h"
#include "imagecheckpage.h"
#include "laboratorycheckpage.h"
#include "othercheckpage.h"

CheckSelectDlg::CheckSelectDlg(QWidget *parent)
    : BaseDialog(parent)
{
    baseUi.btn_title_icon->setIcon(QIcon(":/icons/images/menu.png"));
    baseUi.label_title->setText(tr("诊疗项目选择"));

    resize(864, 644);
    initPageData();
    baseUi.list_view->setCurrentIndex(model->index(0, 0));
    switchPage(model->index(0, 0));
}


void CheckSelectDlg::initPageData() {

    addPageWidget(new BodyCheckPage(this), tr("体格检查"), "BodyCheckPage",  ButtonIdFlag::Button_Application);
    addPageWidget(new ImageCheckPage(this), tr("影像检查"), "ImageCheckPage",  ButtonIdFlag::Button_Application);
    addPageWidget(new LaboratoryCheckPage(this), tr("实验室检查"), "LaboratoryCheckPage", ButtonIdFlag::Button_Application );
    addPageWidget(new OtherCheckPage(this), tr("适宜技术检查"), "OtherCheckPage", ButtonIdFlag::Button_Application );

}

void CheckSelectDlg::on_btn_confirm_clicked()
{
    emit(confirmed(dynamic_cast<DefaultPage*>(baseUi.stacked_widget->currentWidget())->getContent()));
    accept();
}
