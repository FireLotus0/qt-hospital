#include "messagedlg.h"

MessageDlg::MessageDlg(MessageType hint, const QString& text, QWidget *parent)
    : WindowFramelessWidget<QDialog>(parent)
{
    ui.setupUi(this);

    ui.btn_ok->setText(hint == MessageType::Hint_Success ? tr("完成") : tr("确定"));
    setButtonIcon(ui, hint);
    ui.label_info->setText(text);
    connect(ui.btn_ok, &QPushButton::clicked, this, [&](){ accept(); });

    setMoveAreaWidget(ui.widget_title);
}

void MessageDlg::on_btn_close_clicked() {
    reject();
}

MessageDlg *MessageDlg::showDlg(MessageType hint, const QString &text, QWidget *parent) {
    auto dlg = new MessageDlg(hint, text, parent);
    dlg->show();
    return dlg;
}
