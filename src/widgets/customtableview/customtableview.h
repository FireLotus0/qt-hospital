#pragma once

#include <qtableview.h>
#include <qstandarditemmodel.h>
#include <qpushbutton.h>

#include "headerdelegate.h"
#include "tableviewdelegate.h"

class CustomTableView : public QTableView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QTableView)
public:
    explicit CustomTableView(QWidget* parent = nullptr);

    void setCornerButtonText(const QString& text);

    void setHorizontalHeaderLabels(const QStringList& names);

    void insertModelData(const QVariantList& data);

    /**
     * @brief 绘制下拉列表按钮
     * @param [in] orientation 垂直还是水平表头
     * @param [in] index 第几列
     * @param [in] visible 垂直还是水平表头
     */
    void setHeaderViewControl(Qt::Orientation orientation, int index, bool visible);

    void setTableViewColumnColor(int column, const QColor& color);

    QStandardItemModel* getModel();

private:
    QStandardItemModel* model;

    HeaderDelegate* verticalHeader;
    HeaderDelegate* horizontalHeader;

    TableViewDelegate* tableViewDelegate;

    QPushButton* cornerButton;
};
