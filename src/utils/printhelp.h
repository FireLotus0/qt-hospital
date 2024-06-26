
#pragma once
#include <qpdfwriter.h>
#include <qwidget.h>
#include <qprinter.h>

class PrintHelper : public QObject {
    Q_OBJECT //翻译支持

public:
    static void toPdf(QWidget* content);

    static void printWidget(QWidget* widget);

private:
    static void readerToPaintDevice(QWidget *content, QPrinter *printer, QPdfWriter* pdfw = nullptr);
};
