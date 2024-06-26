#pragma once

#include <qwidget.h>

class MessageHintContentWidget;
class MessageHint : public QWidget
{
public:
    static MessageHint * showMessage(const QString& content);

private:
    explicit MessageHint(const QString& content, QWidget *parent = nullptr);

protected:
    QSize sizeHint() const override;

private:
    MessageHintContentWidget * contentWidget;
};

class MessageHintContentWidget : QWidget {
public:
    explicit MessageHintContentWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString content;

    friend class MessageHint;
};