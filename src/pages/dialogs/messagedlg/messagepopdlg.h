#include "utils/windowframelesshelper.h"
#include "ui_messagepopdlg.h"
#include "pages/dialogs/messagedlg/messagedlg.h"

#include <qdialog.h>

class MessagePopDlg : public WindowFramelessWidget<QDialog>
{
    Q_OBJECT

public:
    /**
     * @消息提示对话框
     * @param dlgType 对话框类型
     * @param hint 消息类型
     * @param text 文本
     * @param val 进度条初始数值
     * @param parent
     * @return
     */
    static MessagePopDlg* showDlg(MessageType hint, const QString& text = "", QWidget *parent = nullptr);

protected:
    void focusOutEvent(QFocusEvent *event) override;

private:
    explicit MessagePopDlg(MessageType hint, const QString& text = "", QWidget *parent = nullptr);

private:
    Ui::MessagePopDlg ui{};
};
