#include "datepickerpopup.h"

DatePickerPopup::DatePickerPopup(QDateTime time, QWidget *parent)
    : QWidget(parent)
    , currentDateTime(std::move(time))
{
    ui.setupUi(this);

    setWindowFlags(windowFlags() | Qt::Popup | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    initTableView();
}

void DatePickerPopup::initTableView() {
    dateModel = new QStandardItemModel(this);
    ui.tableView->setModel(dateModel);      //设置数据模型

    /*
     * 功能：表格初始化
     */
    dateModel->setRowCount(6);
    dateModel->setColumnCount(7);
    ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);       //表头自适应

    initTableViewData();

    /*
     * 功能：初始选中索引
     */
    connect(ui.tableView, &QTableView::clicked, this, [&](const QModelIndex& index) {
        auto date = index.data(Qt::UserRole + 1).toDate();
        currentDateTime.setDate(date);
    });
}

void DatePickerPopup::initTableViewData() {
    dateModel->clear();
    auto viewNames = QStringList() << tr("一") << tr("二") << tr("三") << tr("四") << tr("五") << tr("六") << tr("日");
    dateModel->setHorizontalHeaderLabels(viewNames);

    int curYear = currentDateTime.date().year();
    int curMonth = currentDateTime.date().month();
    int curDay = currentDateTime.date().day();

    QDate curDate(curYear, curMonth, curDay);       //当前日期
    int curWeek = curDate.dayOfWeek();              //当前星期

    QDate firstDay(curYear, curMonth, 1);           //当前月第一天
    int dif = curDate.day() - 28;
    if(dif > curWeek) {
        firstDay = firstDay.addDays(dif - curWeek);
    }
    int firstWeek = firstDay.dayOfWeek();           //当前月第一天星期

    auto firstItem = firstDay.addDays(-(firstWeek - 1));
    for(int row = 0; row < 6; row++) {
        for(int col = 0; col < 7; col++) {
            auto item = new QStandardItem;
            item->setText(QString("%1").arg(firstItem.day()));
            item->setTextAlignment(Qt::AlignCenter);
            if(firstItem.year() == curDate.year() && firstItem.month() == curDate.month()) {
                item->setData(QColor(0x1D2129), Qt::ForegroundRole);
            }
            dateModel->setItem(row, col, item);
            dateModel->setData(dateModel->index(row, col), firstItem, Qt::UserRole + 1);
            firstItem = firstItem.addDays(1);
        }
    }

    selectCurrentDate();
    setLabelText();
}

void DatePickerPopup::selectCurrentDate() {
    ui.tableView->selectionModel()->clearSelection();
    QModelIndex index = QModelIndex();
    auto curDate = currentDateTime.date();
    for(int row = 0; row < 5; row++) {
        for(int col = 0; col < 7; col++) {
            auto item = dateModel->data(dateModel->index(row, col), Qt::UserRole + 1).toDate();
            if(curDate == item) {
                index = dateModel->index(row, col);
            }
        }
    }

    if(index.isValid()) {
        ui.tableView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
    }
}

void DatePickerPopup::setLabelText() {
    auto year = currentDateTime.date().year();
    auto month = currentDateTime.date().month();

    ui.lab_year->setText(QString::number(year) + "年");
    ui.lab_month->setText(QString::number(month) + "月");

    emit onDateTimeChanged(currentDateTime);
}

void DatePickerPopup::on_btn_today_clicked() {
    emit onDateTimeChanged(currentDateTime);
    close();
}

void DatePickerPopup::on_btn_left_year_clicked() {
    currentDateTime = currentDateTime.addYears(-1);
    initTableViewData();
}

void DatePickerPopup::on_btn_left_month_clicked() {
    currentDateTime = currentDateTime.addMonths(-1);
    initTableViewData();
}

void DatePickerPopup::on_btn_right_year_clicked() {
    currentDateTime = currentDateTime.addYears(1);
    initTableViewData();
}

void DatePickerPopup::on_btn_right_month_clicked() {
    currentDateTime = currentDateTime.addMonths(1);
    initTableViewData();
}


