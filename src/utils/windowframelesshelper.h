#pragma once

#include <qobject.h>
#include <qevent.h>
#include <qwidget.h>

/**
     * @brief 记录当前鼠标在窗口中所在的区域
     */
enum MouseRegion {
    Window_Left_Border,            ///< 窗口左边框
    Window_Right_Border,           ///< 窗口右边框
    Window_Top_Border,             ///< 窗口上边框
    Window_Bottom_Border,          ///< 窗口下边框
    Window_Left_Top_Corner,        ///< 窗口左上角
    Window_Right_Top_Corner,       ///< 窗口右上角
    Window_Left_Bottom_Corner,     ///< 窗口左下角
    Window_Right_Bottom_Corner,    ///< 窗口右上角
    Window_Internal_Area           ///< 窗口内部区域
};

template<typename T>
class WindowFramelessWidget;

class WindowFramelessHelper : public QWidget
{
public:
    explicit WindowFramelessHelper(QWidget* parent = nullptr);

    void initWidgetMember(QWidget* wid);

    void pressEvent(QMouseEvent *event, QWidget* widget);

    void moveEvent(QMouseEvent *event);

    bool eventFilter(QObject *watched, QEvent *event) override;

    void releaseEvent(QMouseEvent *event);

    MouseRegion getMouseRegion(QPoint mousePos);

    void changeCursorShapeByRegion();

    void stretchWindowByMouse(QMouseEvent *event);

private:
    bool leftButtonPressed = false; ///< 窗口拖动状态标志
    QPoint start;   ///< 窗口拖动的起始位置
    MouseRegion currentMouseRegion = MouseRegion::Window_Internal_Area;     ///< 当前鼠标所在区域
    QWidget* widget;
};

template<typename T>
class WindowFramelessWidget : public T {
public:
    explicit WindowFramelessWidget(QWidget* parent = nullptr) : T(parent){
        //去除默认边框
        this->setWindowFlag(Qt::FramelessWindowHint);
        //开启鼠标悬停事件
        this->setAttribute(Qt::WA_Hover,true);
        this->installEventFilter(&framelessHelper);
        framelessHelper.initWidgetMember((QWidget*)this);

        this->setAttribute(Qt::WA_DeleteOnClose);
        this->setAttribute(Qt::WA_ShowModal);
    }

    /**
     * @brief 窗口拖动开始
     * @note 函数功能全面说明
     *     - 实现窗口拖动开始的判定
     */
    void mousePressEvent(QMouseEvent *event) override {
        framelessHelper.pressEvent(event, moveAreaWidget);
    }

    /**
     * @brief 窗口拖动
     * @note 函数功能全面说明
     *     - 实现窗口拖动过程中窗口位置的计算
     */
    void mouseMoveEvent(QMouseEvent *event) override {
        framelessHelper.moveEvent(event);
    }

    /**
     * @brief 窗口拖动结束
     * @note 函数功能全面说明
     *     - 实现窗口拖动结束的处理
     */
    void mouseReleaseEvent(QMouseEvent *event) override {
        framelessHelper.releaseEvent(event);
    }

    /**
     * @brief 根据鼠标位置，计算当前鼠标在窗口中的区域
     * @param mousePos 鼠标位置
     * @return 窗口区域
     */
    MouseRegion getMouseRegion(QPoint mousePos) {
        return framelessHelper.getMouseRegion(mousePos);
    }

    /**
     * @brief 根据鼠标所在窗口区域，改变鼠标形状
     */
    void changeCursorShapeByRegion() {
        framelessHelper.changeCursorShapeByRegion();
    }

    /**
     * @brief 根据鼠标拉伸窗口，计算窗口size
     */
    void stretchWindowByMouse(QMouseEvent *event) {
        framelessHelper.stretchWindowByMouse(event);
    }

    /**
     * @brief 设置拖动区域组件
     * @param widget
     */
    void setMoveAreaWidget(QWidget* widget) {
        moveAreaWidget = widget;
    }

private:
    WindowFramelessHelper framelessHelper;
    QWidget* moveAreaWidget;    ///< 在此区域点击鼠标可进行拖动
};
