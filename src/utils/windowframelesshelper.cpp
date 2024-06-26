#include "windowframelesshelper.h"

WindowFramelessHelper::WindowFramelessHelper(QWidget* parent)
    : QWidget(parent)
{
}

void WindowFramelessHelper::initWidgetMember(QWidget* wid) {
    widget = wid;
}

bool WindowFramelessHelper::eventFilter(QObject *watched, QEvent *event) {
    if(!leftButtonPressed) {
        if(event->type() == QEvent::HoverEnter || event->type() == QEvent::HoverLeave || event->type()==QEvent::HoverMove) {
            currentMouseRegion = getMouseRegion(QCursor::pos());
            changeCursorShapeByRegion();
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void WindowFramelessHelper::pressEvent(QMouseEvent *event, QWidget* widget) {
    if(widget != nullptr) { //处理拖动事件
        // 鼠标左键按下事件
        if (event->button() == Qt::LeftButton && !widget->window()->isMaximized() && (widget->rect().contains(event->pos()) ||
                                                                                      currentMouseRegion != Window_Internal_Area)) {
            //记录起始位置
            start = event->globalPos();
            // 设置窗口拖动状态
            leftButtonPressed = true;
            return;
        }
    }
    QWidget::mousePressEvent(event);
}

void WindowFramelessHelper::moveEvent(QMouseEvent *event) {
    // 持续按住才能拖动窗口
    if (leftButtonPressed) {
        if(currentMouseRegion == Window_Internal_Area) {
            //将父窗体移动到父窗体原来的位置加上鼠标移动的位置
            widget->move(widget->geometry().topLeft() +
                       event->globalPos() - start);
            //将鼠标在屏幕中的位置替换为新的位置
            start = event->globalPos();
        }
        else {
            stretchWindowByMouse(event);
        }
        return;
    }
    QWidget::mouseMoveEvent(event);
}

void WindowFramelessHelper::releaseEvent(QMouseEvent *event) {
    // 鼠标左键释放
    if (event->button() == Qt::LeftButton) {
        // 重置窗口拖动状态
        leftButtonPressed = false;
        return;
    }
    QWidget::mouseReleaseEvent(event);
}

MouseRegion WindowFramelessHelper::getMouseRegion(QPoint mousePos) {
    auto w = widget->width();
    auto h = widget->height();

    auto x = mousePos.x() - widget->geometry().x();
    auto y = mousePos.y() - widget->geometry().y();
    int offset = 5;

    if (y <= offset && x > offset && x < w - offset) {
        return MouseRegion::Window_Top_Border;
    } else if (x >= w - 4 && y > offset && y < h - offset) {
        return MouseRegion::Window_Right_Border;
    } else if (x <= 4 && y > offset && y < h - offset) {
        return MouseRegion::Window_Left_Border;
    } else if (y >= h - offset && x > offset && x < w - offset) {
        return MouseRegion::Window_Bottom_Border;
    } else if (x >= -offset && x < offset && y >= -offset && y < offset) {
        return Window_Left_Top_Corner;
    } else if (x > w - offset && x <= w + offset && y >= -offset && y < offset) {
        return Window_Right_Top_Corner;
    } else if (x >= -offset && x < offset && y > h - offset && y <= h + offset) {
        return Window_Left_Bottom_Corner;
    } else if (x > w - offset && x <= w + offset && y > h - offset && y <= h + offset) {
        return Window_Right_Bottom_Corner;
    }

    return Window_Internal_Area;
}

void WindowFramelessHelper::changeCursorShapeByRegion() {
    switch(currentMouseRegion) {
        case Window_Top_Border:
        case Window_Bottom_Border:
            widget->setCursor(Qt::SizeVerCursor);
            break;
        case Window_Left_Border:
        case Window_Right_Border:
            widget->setCursor(Qt::SizeHorCursor);
            break;
        case Window_Left_Top_Corner:
        case Window_Right_Bottom_Corner:
            widget->setCursor(Qt::SizeFDiagCursor);
            break;
        case Window_Left_Bottom_Corner:
        case Window_Right_Top_Corner:
            widget->setCursor(Qt::SizeBDiagCursor);
            break;
        default:
            widget->setCursor(Qt::ArrowCursor);
            break;
    }
}

void WindowFramelessHelper::stretchWindowByMouse(QMouseEvent *event) {

    auto windowGeometry = widget->geometry();
    auto minHeight = widget->minimumHeight();
    auto minWidth = widget->minimumWidth();
    auto globalPosY = event->globalPos().y();
    auto globalPosX = event->globalPos().x();
    auto localPosX = event->pos().x();
    auto localPosY = event->pos().y();
    auto width = widget->width();
    auto height = widget->height();

    switch(currentMouseRegion) {
        case Window_Top_Border:
            windowGeometry.setTop(windowGeometry.bottom() - globalPosY > minHeight ? globalPosY : windowGeometry.top());
            widget->setGeometry(windowGeometry);
            break;
        case Window_Left_Top_Corner:
            windowGeometry.setTop(windowGeometry.bottom() - globalPosY > minHeight ? globalPosY : windowGeometry.top());
            windowGeometry.setLeft(windowGeometry.right() - globalPosX > minWidth ? globalPosX : windowGeometry.left());
            widget->setGeometry(windowGeometry);
            break;
        case Window_Right_Top_Corner:
            windowGeometry.setTop(windowGeometry.bottom() - globalPosY > minHeight ? globalPosY : windowGeometry.top());
            windowGeometry.setRight(globalPosX - windowGeometry.left() > minWidth ? globalPosX : windowGeometry.left() + minWidth -1);
            widget->setGeometry(windowGeometry);
            break;
        case Window_Left_Border:
            windowGeometry.setLeft(windowGeometry.right() - globalPosX > minWidth ? globalPosX : windowGeometry.left());
            widget->setGeometry(windowGeometry);
            break;
        case Window_Right_Border:
            width = widget->width() - (widget->width() - localPosX);
            widget->resize(width, height);
            break;
        case Window_Bottom_Border:
            height = widget->height() - (widget->height() - localPosY);
            widget->resize(width, height);
            break;
        case Window_Left_Bottom_Corner:
            windowGeometry.setBottom(globalPosY - windowGeometry.top() > minHeight ? globalPosY : windowGeometry.bottom());
            windowGeometry.setLeft(windowGeometry.right() - globalPosX > minWidth ? globalPosX : windowGeometry.left());
            widget->setGeometry(windowGeometry);
            break;
        case Window_Right_Bottom_Corner:
            width = widget->width() - (widget->width() - localPosX);
            height = widget->height() - (widget->height() - localPosY);
            widget->resize(width, height);
            break;
        default:
            break;
    }
}
