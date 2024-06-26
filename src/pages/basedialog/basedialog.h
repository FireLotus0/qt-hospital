#pragma once

#include "ui_basedialog.h"
#include "utils/windowframelesshelper.h"

#include <qstandarditemmodel.h>
#include <qdialog.h>

enum ButtonIdFlag {
    Button_Arg_Config_1 = 1,
    Button_Arg_Config_2 = Button_Arg_Config_1 << 1,
    Button_Sys_Config_1 = Button_Arg_Config_2 << 1,
    Button_Sys_Config_2 = Button_Sys_Config_1 << 1,
    Button_Application = Button_Sys_Config_2 << 1
};
Q_DECLARE_FLAGS(ButtonIdFlags, ButtonIdFlag)
Q_DECLARE_OPERATORS_FOR_FLAGS(ButtonIdFlags)

/**
 * @brief 页面初始设置数据
 */
struct PageInitData {
    QByteArray itemText = "";      ///< 节点文本
    QByteArray pageName = "";      ///< 页面名
    ButtonIdFlags flags;        ///< 页面显示按钮ID标记
};
Q_DECLARE_METATYPE(PageInitData)

class BaseDialog : public WindowFramelessWidget<QDialog>
{
    Q_OBJECT

public:
    explicit BaseDialog(QWidget *parent = nullptr);

protected:

    void paintEvent(QPaintEvent *event) override;

public slots:

    /**
     * @brief 点击退出
     * @return
     */
    void on_btn_close_clicked();

    virtual void on_btn_confirm_clicked();

protected:

    /**
     * @brief 根据是否设置按钮文字，决定按钮是否显示
     */
     void setButtonVisible(ButtonIdFlags flags);

    /**
     * @brief 添加页面
     * @param
     */
    void addPageWidget(QWidget* widget, const QString& itemText, const QString& pageName, ButtonIdFlags flags);

    /**
     * @brief 点击节点，进行页面切换
     * @param index
     */
     void switchPage(const QModelIndex& index);

     /**
      * @brief 设置底部按钮widget是否显示
      * @param visiable
      */
     void setBottomVisible(bool visible);

     /**
      * @brief 设置左上角图标是否显示
      * @param visible
      */
     void setIconVisible(bool visible);

protected:
    Ui::BaseDialog baseUi{};
    QStandardItemModel* model;
    QList<ButtonIdFlags> pageInitDataList; ///< 页面初始数据列表
};
