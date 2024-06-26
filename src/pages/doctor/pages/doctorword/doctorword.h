#include "ui_doctorword.h"

#include <QWidget>

class DoctorWords : public QWidget
{
    Q_OBJECT

public:
    DoctorWords(QWidget* parent = nullptr);

private:
    Ui::DoctorWord ui;
};
