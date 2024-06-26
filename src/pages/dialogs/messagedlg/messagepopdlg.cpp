#include "messagepopdlg.h"

MessagePopDlg::MessagePopDlg(MessageType hint, const QString& text, QWidget *parent)
    : WindowFramelessWidget<QDialog>(parent)
{
    ui.setupUi(this);
    MessageDlg::setButtonIcon(ui, hint);
    ui.label_info->setText(text);
    setWindowModality(Qt::NonModal);
    setFocus();
}

MessagePopDlg *MessagePopDlg::showDlg(MessageType hint, const QString &text, QWidget *parent) {
    auto dlg = new MessagePopDlg(hint, text, parent);
    dlg->show();
    return dlg;
}

void MessagePopDlg::focusOutEvent(QFocusEvent *event) {
    this->close();
}