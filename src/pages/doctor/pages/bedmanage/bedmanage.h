#include "ui_bedmanage.h"

#include <QWidget>

class BedManage : public QWidget
{
    Q_OBJECT

public:
    BedManage(QWidget* parent = nullptr);

private:
    Ui::BedManage ui;
};
