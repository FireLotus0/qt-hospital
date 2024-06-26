#include "progressbardlg.h"

#include "pages/dialogs/messagedlg/messagepopdlg.h"

#include <QTimer>


ProgressBarDlg::ProgressBarDlg(int val, QWidget *parent)
    : WindowFramelessWidget<QDialog>(parent)
{
    ui.setupUi(this);
    setMoveAreaWidget(ui.widget_title);

    ui.btn_1->setText(tr("取消"));
    ui.btn_2->setText(tr("完成"));
    setProgressBarValue(val);
    connect(ui.progressBar, &QProgressBar::valueChanged, this, [&](int value) {
            ui.label_progress_val->setText(QString("%1%").arg(value));
            ui.btn_2->setText(tr("完成"));
            ui.btn_2->setEnabled(value == ui.progressBar->maximum());
        });

    connect(ui.btn_1, &QPushButton::clicked, this, [&]() { emit(btnCancelClicked()); reject(); });
    connect(ui.btn_2, &QPushButton::clicked, this, [&]() { accept(); });
    emit(ui.progressBar->valueChanged(val));
}

void ProgressBarDlg::on_btn_close_clicked() {
    reject();
}

void ProgressBarDlg::setProgressBarValue(int val) {
    ui.progressBar->setValue(val);

}

ProgressBarDlg *ProgressBarDlg::showDlg(int val, QWidget *parent) {
    auto dlg = new ProgressBarDlg(val, parent);
    dlg->setModal(false);
    dlg->show();
    return dlg;
}

void ProgressBarDlg::setValue(int val)
{
    ui.progressBar->setValue(val);
    if(val == 100) {
        MessagePopDlg::showDlg(MessageType::Hint_Success, "预约成功！", this);
    }
}

void ProgressBarDlg::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
