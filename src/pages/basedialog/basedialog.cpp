#include "basedialog.h"

#include <qpainter.h>

BaseDialog::BaseDialog(QWidget *parent)
    : WindowFramelessWidget<QDialog>(parent)
{
    baseUi.setupUi(this);
    model = new QStandardItemModel(this);
    baseUi.list_view->setModel(model);
    setMoveAreaWidget(baseUi.widget_title);
    //切换页面
    connect(baseUi.list_view, &QListView::clicked, this, &BaseDialog::switchPage);
}

void BaseDialog::on_btn_close_clicked() {
    reject();
}

void BaseDialog::on_btn_confirm_clicked()
{
}

void BaseDialog::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void BaseDialog::setButtonVisible(ButtonIdFlags flags) {
    baseUi.btn_arg_config_1->setVisible(flags.testFlag(Button_Arg_Config_1));
    baseUi.btn_arg_config_2->setVisible(flags.testFlag(Button_Arg_Config_2));
    baseUi.btn_sys_config_1->setVisible(flags.testFlag(Button_Sys_Config_1));
    baseUi.btn_sys_config_2->setVisible(flags.testFlag(Button_Sys_Config_2));
    baseUi.btn_confirm->setVisible(flags.testFlag(Button_Application));
}

void BaseDialog::addPageWidget(QWidget* widget, const QString &itemText, const QString &pageName, ButtonIdFlags flags) {
    int oldRowCount = model->rowCount();
    model->setRowCount(oldRowCount + 1);
    QStandardItem* item;
    item = new QStandardItem(itemText);    //创建节点
    item->setTextAlignment(Qt::AlignCenter);
    model->setItem(oldRowCount, item);
    baseUi.stacked_widget->addWidget(widget);

    pageInitDataList<<flags;
}

void BaseDialog::switchPage(const QModelIndex &index) {
    if(index.isValid()) {
        setButtonVisible(pageInitDataList[index.row()]);
        baseUi.stacked_widget->setCurrentIndex(index.row());
    }

}

void BaseDialog::setBottomVisible(bool visible) {
    baseUi.widget->setVisible(visible);
}

void BaseDialog::setIconVisible(bool visible) {
    baseUi.btn_title_icon->setVisible(visible);
    if(!visible) {
        baseUi.widget_title->setContentsMargins(12, 0, 0, 6);
    }
}
