#pragma once

#include "ui_alarmingrecorddialog.h"
#include "appsetting.h"
#include <qdialog.h>
#include <qstandarditemmodel.h>

enum RecordType{
    All_Record,     ///< 综合门诊
    Common_Record,  ///< 普通门诊
    Health_Record,  ///< 保健门诊
    Hurry_Record    ///< 急诊
};
Q_DECLARE_METATYPE(RecordType)

class RecordDialog : public QWidget
{
    Q_OBJECT

public:
    explicit RecordDialog(QWidget *parent = nullptr);

private:
    /**
     * @brief 设置table属性
     */
    void initTableProperty();

    /**
     * 更新按钮checked状态
     * @param btn
     */
    void updateButtonCheckStatus(QPushButton* btn);

    /**
     * @brief 根据标签从数据库加载数据
     * @param [in] dataType 标签
     */
    void loadData(RecordType tag);

public slots:
    /**
     * @brief 点击切换页面
     */
    void clickToSwitchPage();

    void on_btn_find_clicked();

public:
    static void loadDataHelp(PatientInfo& info, QJsonObject& data);

signals:
    void itemSelected();

private:
    Ui::AlarmingRecordDialog ui{};
    QStandardItemModel* model{nullptr};
    QList<PatientInfo> dataList;
    RecordType curTag;
};
