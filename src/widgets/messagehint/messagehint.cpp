#include "messagehint.h"

#include <qboxlayout.h>
#include <qgraphicseffect.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qdebug.h>

#define PADDING 5

MessageHint *MessageHint::showMessage(const QString &content) {
    auto dlg = new MessageHint(content);
    dlg->show();
    return dlg;
}

MessageHint::MessageHint(const QString &content, QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(windowFlags() | Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground);

    setStyleSheet("font-size：14px");

    auto hBox = new QHBoxLayout(this);
    hBox->setContentsMargins(PADDING, PADDING, PADDING, PADDING);

    contentWidget = new MessageHintContentWidget(this);
    contentWidget->content = content;
    hBox->addWidget(contentWidget);

    auto graphicsEffect = new QGraphicsDropShadowEffect(this);
    graphicsEffect->setOffset(0, 0);    //设置阴影无偏移
    graphicsEffect->setBlurRadius(5);
    graphicsEffect->setColor(0xC0C0C0);
    contentWidget->setGraphicsEffect(graphicsEffect);
}

QSize MessageHint::sizeHint() const {
    return QSize(fontMetrics().horizontalAdvance(contentWidget->content) + 32, fontMetrics().height() + 16 + 7) + QSize(PADDING * 2, PADDING * 2);
}

MessageHintContentWidget::MessageHintContentWidget(QWidget *parent)
    : QWidget(parent)
{
}

void MessageHintContentWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    //设置抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;       //设置画刷
    brush.setStyle(Qt::SolidPattern);
    brush.setColor("#FFFFFF");
    painter.setBrush(brush);
    painter.setPen(QColor(Qt::white));

    QRect ta(16, 0, 14, 7);
    //ta.translate(PADDING, PADDING);
    QPainterPath painterPath;
    painterPath.moveTo(ta.bottomLeft());
    painterPath.lineTo(QPoint(ta.center().x(), ta.top()));
    painterPath.lineTo(ta.bottomRight());
    painterPath.closeSubpath();

    QPainterPath textRectPath;
    QRect textRect(0, ta.bottom(), width(), height() - ta.height());
    //textRect.adjust(PADDING, 0, -PADDING, -PADDING);
    textRectPath.addRect(textRect);
    painter.fillPath(painterPath + textRectPath, QColor(Qt::white));

    //画文字
    painter.setPen(QColor("#F5222D"));
    painter.drawText(textRect, Qt::AlignCenter, content);
}
