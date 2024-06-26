#include "mainpage.h"
#include <QTreeView>
#include "pages/patientselect/patientselect.h"
#include "pages/patientrecord/patientrecord.h"
#include "pages/doctorword/doctorword.h"
#include "pages/bedmanage/bedmanage.h"

MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    model = new QStandardItemModel(this);
    ui.treeView->setModel(model);
    ui.treeView->setHeaderHidden(true);
    initTree();
    initStackWidget();
    initSignalSlots();
    ui.treeView->expandAll();
}

void MainPage::initTree()
{
    auto* root = new QStandardItem;
    root->setText("业务处理");
    root->setIcon(QIcon(":/icons/images/works.png"));
    model->setItem(0, 0, root);

    auto doctorInfo = new QStandardItem("信息科主任");
    doctorInfo->setIcon(QIcon(":/icons/images/doctor.png"));
    doctorInfo->setData(0, Qt::UserRole + 1);
    root->setChild(0, 0, doctorInfo);

    auto doctorWordTest = new QStandardItem("医嘱测试");
    doctorWordTest->setIcon(QIcon(":/icons/images/doctorword.png"));
    doctorWordTest->setData(1, Qt::UserRole + 1);
    doctorInfo->setChild(0, 0, doctorWordTest);

    auto doctorWord = new QStandardItem("医嘱");
    doctorWord->setIcon(QIcon(":/icons/images/docWord.png"));
    doctorWord->setData(2, Qt::UserRole + 1);
    doctorWordTest->setChild(0, 0, doctorWord);

    auto checkItem = new QStandardItem("检验");
    checkItem->setIcon(QIcon(":/icons/images/check.png"));
    doctorWordTest->setChild(1, 0, checkItem);

    auto inspectItem = new QStandardItem("检查");
    inspectItem->setIcon(QIcon(":/icons/images/inspect.png"));
    doctorWordTest->setChild(2, 0, inspectItem);

    auto operationItem = new QStandardItem("手术");
    operationItem->setIcon(QIcon(":/icons/images/operation.png"));
    doctorWordTest->setChild(3, 0, operationItem);

    auto benManageItem = new QStandardItem("床位管理");
    benManageItem->setIcon(QIcon(":/icons/images/bed.png"));
    benManageItem->setData(3, Qt::UserRole + 1);
    root->setChild(1, 0, benManageItem);
}

void MainPage::initSignalSlots()
{
    connect(ui.treeView, &QTreeView::clicked, this, [&](const QModelIndex& index){
        if(index.isValid()) {
            ui.stackedWidget->setCurrentIndex(index.data(Qt::UserRole + 1).toInt());
        }
    }
    );
}

void MainPage::initStackWidget()
{
    //默认界面
    auto widget = new PatientSelect(this);
    ui.stackedWidget->addWidget(widget);

    //医嘱测试界面
    auto widgetRecord = new PatientRecord(this);
    ui.stackedWidget->addWidget((QWidget*)widgetRecord);

    //医嘱界面
    auto doctorWords = new DoctorWords(this);
    ui.stackedWidget->addWidget((QWidget*)doctorWords);

    //床位管理界面
    auto bedManage = new BedManage(this);
    ui.stackedWidget->addWidget((QWidget*)bedManage);
}
