
#include "ui_outpatientservice.h"
#include <QWidget>

class OutpatientService : public QWidget
{
    Q_OBJECT
public:
    explicit OutpatientService(QWidget* parent = nullptr);

private:

    void iniUi();

    void updatePatient();

public slots:


private:
    Ui::OutpatientService ui{};
};
