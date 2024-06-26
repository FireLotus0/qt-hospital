#include "printhelp.h"
#include <QPagedPaintDevice>
#include <qfiledialog.h>
#include <qpainter.h>
#include <QPrintPreviewDialog>
#include <qdebug.h>

void PrintHelper::toPdf(QWidget *content) {
    QString filename=QFileDialog::getSaveFileName(nullptr, "另存为pdf文件","./","*.pdf");
    if(!filename.contains(".pdf"))
    {
        filename=filename + ".pdf";
    }
    QPdfWriter pdfw(filename);
    QPageLayout qpagelay;
    qpagelay.setPageSize(QPageSize(QPageSize::A4));
    qpagelay.setOrientation(QPageLayout::Landscape);
    qpagelay.setMargins(QMargins(0,40,0,0));
    pdfw.setPageLayout(qpagelay);
    readerToPaintDevice(content, nullptr, &pdfw);
}

void PrintHelper::printWidget(QWidget *widget)
{
    QPrintPreviewDialog dlg;
    connect(&dlg, &QPrintPreviewDialog::paintRequested, [=](QPrinter* printer){
        readerToPaintDevice(widget, printer);
    });
    dlg.exec();
}

void PrintHelper::readerToPaintDevice(QWidget *content, QPrinter *printerDevice, QPdfWriter* pdfw)
{
    QPagedPaintDevice* printer;
    if(pdfw == nullptr) {
        printer = printerDevice;
    } else {
        printer = pdfw;
    }
    auto contentSize = content->size();
    //计算画布缩放比
    int logicalDPIX = printer->logicalDpiX();
    auto pageSize = printer->pageLayout().pageSize();

    qreal pdfWidth = pageSize.rectPixels(logicalDPIX - 48).width();
    qreal scale = pdfWidth / content->width();

    //计算单个页面可以绘制的大小
    auto paintRect = printer->pageLayout().paintRect();
    qreal contentRatio = paintRect.width() / paintRect.height();
    auto validRenderRect = QRectF(0, 0, contentSize.width(), contentSize.width() / contentRatio);

    QPainter painter(printer);

    painter.scale(scale, scale);
    //循环绘制
    qreal yOffset = 0;
    do {
        validRenderRect.moveTop(yOffset); //偏移，不绘制其他页面的部分
        content->render(&painter, QPoint(0, 0), QRegion(validRenderRect.toRect())); //截断，只绘制当前页
        yOffset += validRenderRect.height(); //计算下一页开始位置
        if (yOffset > contentSize.height()) {
            break;
        }
        //当前页绘制控件可能会超出绘制区域，填充白色清空区域
        painter.fillRect(0, qRound(validRenderRect.height()), qRound(validRenderRect.width()), 100, Qt::white);
        //当前页面不够绘制，切换到下一页
        printer->newPage();
    } while (true);
}
