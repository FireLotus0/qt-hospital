#include "ui_checkitempage.h"
#include "widgets/checkitem.h"
#include "appsetting.h"

#include <QWidget>


class CheckItemPage : public QWidget
{
    Q_OBJECT

public:
    CheckItemPage(QWidget* parent = nullptr);

public slots:

    void on_btn_add_clicked();

    void on_btn_delete_clicked();

    void on_btn_generate_clicked();

    void on_btn_print_clicked();

    void on_btn_pdf_clicked();

    void on_btn_commit_clicked();
private:
    void iniUi();

    void initSigSlots();

private:
    Ui::CheckItemPage ui;
    QList<CheckItem*> dataItem;
    QList<CheckProject> dataList;
};
