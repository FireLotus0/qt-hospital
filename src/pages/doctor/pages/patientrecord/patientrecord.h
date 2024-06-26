#include "ui_patientrecord.h"

#include <QWidget>

class PatientRecord : public QWidget
{
    Q_OBJECT

public:
    PatientRecord(QWidget* parent = nullptr);

private:
    Ui::PatientRecord ui;
};
