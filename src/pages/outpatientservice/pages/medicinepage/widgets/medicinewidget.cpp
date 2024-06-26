#include "medicinewidget.h"
#include "pages/dialogs/messagedlg/messagedlg.h"

MedicineWidget::MedicineWidget(int i, QWidget *parent)
    : QWidget(parent)
    , id(i)
{
    ui.setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
    initSigSlots();
}

void MedicineWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton) {
        auto dlg = MessageDlg::showDlg(MessageType::Hint_Help, "是否删除当前药品?");
        connect(dlg, &MessageDlg::accepted, this, [&]() {
            emit(deleteMedicine(id));
        });
    } else if(event->button() == Qt::LeftButton) {
        emit widgetClicked(this);
    }
    return QWidget::mousePressEvent(event);
}

void MedicineWidget::setText(const QStringList &info)
{
    ui.lineEdit_name->setText(info[0]);
    ui.lineEdit_price->setText(info[1]);
    ui.lineEdit_special->setText(info[2]);
}

void MedicineWidget::initSigSlots()
{
    connect(ui.lineEdit_nums, &QLineEdit::textChanged, this, [&](const QString& num){
        auto ok = false;
        int nums = num.toInt(&ok);
        if(ok) {
            ok = false;
            auto price = ui.lineEdit_price->text().toDouble(&ok);
            if(ok) {
                ui.lineEdit_money->setText(QString::number(price * nums));
            } else {
                ui.lineEdit_money->setText("0.0");
            }
        }
    });
}


