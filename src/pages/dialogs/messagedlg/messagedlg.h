#pragma once

#include "utils/windowframelesshelper.h"
#include "ui_messagedlg.h"

#include <qdialog.h>

/**
 * @brief 提示消息类型
 */
enum MessageType
{
    Hint_Warn,
    Hint_Error,
    Hint_Success,
    Hint_Help,
};

class MessageDlg : public WindowFramelessWidget<QDialog>
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
    static MessageDlg* showDlg(MessageType hint, const QString& text = "", QWidget *parent = nullptr);

    template<typename U>
    static void setButtonIcon(U ui, MessageType hint) {
        QString iconPath;
        switch(hint) {
            case MessageType::Hint_Warn:
                iconPath = ":/icons/images/icon_warning1.png";
                break;
            case MessageType::Hint_Error:
                iconPath = ":/icons/images/icon_error.png";
                break;
            case MessageType::Hint_Success:
                iconPath = ":/icons/images/icon_success.png";
                break;
            case MessageType::Hint_Help:
                iconPath = ":/icons/images/icon_help2.png";
                break;
        }
        ui.btn_icon->setIcon(QIcon(iconPath));
    }

private:
    explicit MessageDlg(MessageType hint, const QString& text = "", QWidget *parent = nullptr);

public slots:
    void on_btn_close_clicked();

private:
    Ui::MessageDlg ui{};
};
