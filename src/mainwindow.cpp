#include "mainwindow.h"
#include "homepage.h"
#include "toptoolbar.h"
#include "infoframe.h"
#include "monitorframe.h"
#include "cleanframe.h"
#include "toolsframe.h"
#include "extensionedgewidget.h"
#include "rightpanel.h"
#include "contants.h"

#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QScreen>
#include <QTimer>
#include <QCloseEvent>
#include <QPainter>
#include <QBitmap>
#include <QDebug>
#include <QStackedLayout>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QStackedWidget>
#include <QShortcut>
#include <QKeySequence>
#include <QTimer>

#define STRETCH_RECT_HEIGHT 4       // 拉伸小矩形的高度;
#define STRETCH_RECT_WIDTH 4        // 拉伸小矩形的宽度;

namespace {
const int MAINWIDGET_MINIMUN_HEIGHT = 480;
const int MAINWIDGET_MINIMUN_WIDTH = 640;
const int Padding = 2;
//const int EXTENSION_PANEL_WIDTH = 300;
const int TOP_TOOLBAR_HEIGHT = 56;

//该动画效果用于编写向导页面： 界面切换动画从右边往左边切换(从右到左)
//topWidget: 将要被移走的界面
//bottomWidget: 将要显示的界面
//delay: 动画时长
void switchWidgetFromRightToLeft(QWidget *leftWidget, QWidget *rightWidget, int delay)
{
    rightWidget->show();
    leftWidget->show();

    QRect leftStartRect = QRect(0, 0, leftWidget->width(), leftWidget->height());
    QRect leftEndRect = leftStartRect;
    leftEndRect.setX(-leftWidget->width());

    QPropertyAnimation *leftAnimation = new QPropertyAnimation(leftWidget, "geometry");
    leftAnimation->setDuration(delay);
    leftAnimation->setStartValue(leftStartRect);
    leftAnimation->setEndValue(leftEndRect);
    leftAnimation->start();

    QRect rightStartRect = QRect(leftWidget->width(), 0, rightWidget->width(), rightWidget->height());
    QRect rightEndRect = leftStartRect;
    leftEndRect.setX(0);

    QPropertyAnimation *rightAnimation = new QPropertyAnimation(rightWidget, "geometry");
    rightAnimation->setDuration(delay);
    rightAnimation->setStartValue(rightStartRect);
    rightAnimation->setEndValue(rightEndRect);
    rightAnimation->start();

    leftAnimation->connect(leftAnimation, &QPropertyAnimation::finished, leftAnimation, &QPropertyAnimation::deleteLater);
    rightAnimation->connect(rightAnimation, &QPropertyAnimation::finished, rightAnimation, &QPropertyAnimation::deleteLater);
    rightAnimation->connect(rightAnimation, &QPropertyAnimation::finished, leftWidget, &QWidget::hide);

//    QParallelAnimationGroup *animationGroup = new QParallelAnimationGroup;
//    animationGroup->addAnimation(leftAnimation);
//    animationGroup->addAnimation(rightAnimation);
//    connect(animationGroup, SIGNAL(finished()), this, SLOT(upAnimFinished()));
//    animationGroup->connect(animationGroup, &QParallelAnimationGroup::finished, leftWidget, [=] () {
//        leftAnimation->deleteLater();
//        rightAnimation->deleteLater();
//        leftWidget->hide();
//    });
//    animationGroup->start();
}

//w: 将要显示或隐藏的界面
//startRect: 界面滑动之前的区域坐标
//endRect: 界面滑动之后的区域坐标
//delay: 动画时长
//hide: 为true时为隐藏界面，为false时为显示界面
void slideEdgeWidget(QWidget *w, QRect startRect, QRect endRect, int delay, bool hide)
{
    w->show();

    QPropertyAnimation *animation = new QPropertyAnimation(w, "geometry");
    animation->setEasingCurve(QEasingCurve::InCurve);
    animation->setDuration(delay);
    animation->setStartValue(startRect);
    animation->setEndValue(endRect);
    animation->start();
    animation->connect(animation, &QPropertyAnimation::finished, animation, &QPropertyAnimation::deleteLater);
    if (hide) {
        animation->connect(animation, &QPropertyAnimation::finished, w, &QWidget::hide);
    }
}

//界面切换动画从底部往顶部切换(从下到上)
//topWidget: 将要被移走的界面
//bottomWidget: 将要显示的界面
//delay: 动画时长
void switchWidgetFromBottomToTop(QWidget *topWidget, QWidget *bottomWidget, int delay)
{
    bottomWidget->show();
    topWidget->show();

    QRect topStartRect = QRect(0, 0, topWidget->width(), topWidget->height());
    QRect topEndRect = topStartRect;
    topEndRect.moveTop(-topWidget->height());

    QPropertyAnimation *topAnimation = new QPropertyAnimation(topWidget, "geometry");
    topAnimation->setDuration(delay);
    topAnimation->setEasingCurve(QEasingCurve::InOutCubic);
    topAnimation->setStartValue(topStartRect);
    topAnimation->setEndValue(topEndRect);
    topAnimation->start();
    topAnimation->connect(topAnimation, &QPropertyAnimation::finished, topAnimation, &QPropertyAnimation::deleteLater);
    topAnimation->connect(topAnimation, &QPropertyAnimation::finished, topWidget, &QWidget::hide);

    QRect bottomStartRect = QRect(0, topWidget->height(), bottomWidget->width(), bottomWidget->height());
    QRect bottomEndRect = bottomStartRect;
    bottomEndRect.moveTo(0, 0);

    QPropertyAnimation *bottomAnimation = new QPropertyAnimation(bottomWidget, "geometry");
    bottomAnimation->setEasingCurve(QEasingCurve::InOutCubic);
    bottomAnimation->setDuration(delay);
    bottomAnimation->setStartValue(bottomStartRect);
    bottomAnimation->setEndValue(bottomEndRect);
    bottomAnimation->start();
    bottomAnimation->connect(bottomAnimation, &QPropertyAnimation::finished, bottomAnimation, &QPropertyAnimation::deleteLater);

    auto bottomOpacity = new QGraphicsOpacityEffect(bottomWidget);
    bottomWidget->setGraphicsEffect(bottomOpacity);
    bottomOpacity->setOpacity(0);
    QPropertyAnimation *bottomOpacityAnimation = new QPropertyAnimation(bottomOpacity, "opacity");
    bottomOpacityAnimation->setEasingCurve(QEasingCurve::InCubic);
    bottomOpacityAnimation->setDuration(delay);
    bottomOpacityAnimation->setStartValue(0.0);
    bottomOpacityAnimation->setEndValue(1.0);
    bottomOpacityAnimation->start();
    bottomOpacityAnimation->connect(bottomOpacityAnimation, &QPropertyAnimation::finished, bottomOpacityAnimation, &QPropertyAnimation::deleteLater);
    bottomOpacityAnimation->connect(bottomOpacityAnimation, &QPropertyAnimation::finished, bottomWidget, [=] () {
        bottomWidget->setGraphicsEffect(nullptr);
    });

    auto topOpacity = new QGraphicsOpacityEffect();
    topWidget->setGraphicsEffect(topOpacity);
    topOpacity->setOpacity(1);
    QPropertyAnimation *topOpacityAnimation = new QPropertyAnimation(topOpacity, "opacity");
    topOpacityAnimation->setEasingCurve(QEasingCurve::InCubic);
    topOpacityAnimation->setDuration(delay);
    topOpacityAnimation->setStartValue(1.0);
    topOpacityAnimation->setEndValue(0.0);
    topOpacityAnimation->start();
    topOpacityAnimation->connect(topOpacityAnimation, &QPropertyAnimation::finished, topOpacityAnimation, &QPropertyAnimation::deleteLater);
    topOpacityAnimation->connect(topOpacityAnimation, &QPropertyAnimation::finished, topWidget, [=] () {
        topWidget->setGraphicsEffect(nullptr);
    });
}

//界面切换动画从顶部往底部切换(从上到下)
//topWidget: 将要被移走的界面
//bottomWidget: 将要显示的界面
//delay: 动画时长
void switchWidgetFromTopToBottom(QWidget *topWidget, QWidget *bottomWidget, int delay)
{
    bottomWidget->show();
    topWidget->show();

    QRect topStartRect = QRect(0, 0, topWidget->width(), topWidget->height());
    QRect topEndRect = topStartRect;
    topEndRect.moveTo(0, topWidget->height());

    QPropertyAnimation *topWidgetAnimation = new QPropertyAnimation(topWidget, "geometry");
    topWidgetAnimation->setDuration(delay);
    topWidgetAnimation->setEasingCurve(QEasingCurve::InOutCubic);
    topWidgetAnimation->setStartValue(topStartRect);
    topWidgetAnimation->setEndValue(topEndRect);
    topWidgetAnimation->start();
    topWidgetAnimation->connect(topWidgetAnimation, &QPropertyAnimation::finished, topWidgetAnimation, &QPropertyAnimation::deleteLater);
    topWidgetAnimation->connect(topWidgetAnimation, &QPropertyAnimation::finished, topWidget, &QWidget::hide);

    QRect bottomStartRect = QRect(0, -topWidget->height(), bottomWidget->width(), bottomWidget->height());
    QRect bottomEndRect = bottomStartRect;
    bottomEndRect.moveBottom(topWidget->height() - 1);

    QPropertyAnimation *bottomAnimation = new QPropertyAnimation(bottomWidget, "geometry");
    bottomAnimation->setEasingCurve(QEasingCurve::InOutCubic);
    bottomAnimation->setDuration(delay);
    bottomAnimation->setStartValue(bottomStartRect);
    bottomAnimation->setEndValue(bottomEndRect);
    bottomAnimation->start();
    bottomAnimation->connect(bottomAnimation, &QPropertyAnimation::finished, bottomAnimation, &QPropertyAnimation::deleteLater);

    auto bottomOpacity = new QGraphicsOpacityEffect(bottomWidget);
    bottomWidget->setGraphicsEffect(bottomOpacity);
    bottomOpacity->setOpacity(0);

    QPropertyAnimation *bottomOpacityAnimation = new QPropertyAnimation(bottomOpacity, "opacity");
    bottomOpacityAnimation->setEasingCurve(QEasingCurve::InCubic);
    bottomOpacityAnimation->setDuration(delay);
    bottomOpacityAnimation->setStartValue(0.0);
    bottomOpacityAnimation->setEndValue(1.0);
    bottomOpacityAnimation->start();
    bottomOpacityAnimation->connect(bottomOpacityAnimation, &QPropertyAnimation::finished, bottomOpacityAnimation, &QPropertyAnimation::deleteLater);
    bottomOpacityAnimation->connect(bottomOpacityAnimation, &QPropertyAnimation::finished, bottomWidget, [=] () {
        bottomWidget->setGraphicsEffect(nullptr);
    });

    auto topOpacity = new QGraphicsOpacityEffect(topWidget);
    topWidget->setGraphicsEffect(topOpacity);
    topOpacity->setOpacity(0.99);

    QPropertyAnimation *topOpacityAnimation = new QPropertyAnimation(topOpacity, "opacity");
    topOpacityAnimation->setEasingCurve(QEasingCurve::InCubic);
    topOpacityAnimation->setDuration(delay);
    topOpacityAnimation->setStartValue(1.0);
    topOpacityAnimation->setEndValue(0.0);
    topOpacityAnimation->start();
    topOpacityAnimation->connect(topOpacityAnimation, &QPropertyAnimation::finished, topOpacityAnimation, &QPropertyAnimation::deleteLater);
    topOpacityAnimation->connect(topOpacityAnimation, &QPropertyAnimation::finished, bottomWidget, [=] () {
        topWidget->setGraphicsEffect(nullptr);
    });
}

}

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent)
    , m_mousePress(false)
    , m_edgeShowed(false)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowIcon(QIcon(":/res/system-manager.png"));
    this->setWindowTitle(tr("system-manager"));
    this->setMouseTracking(true);

    this->setMouseTracking(true);

    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    this->setFocusPolicy(Qt::StrongFocus);
    this->resize(900, 600);
    this->setMinimumSize(MAINWIDGET_MINIMUN_WIDTH, MAINWIDGET_MINIMUN_HEIGHT);

    m_currentWidget = NULL;

    m_titlebar = new TopToolBar;
    m_titlebar->setFixedHeight(46);
    this->setMenuWidget(m_titlebar);

    m_homeWidget = new HomeWidget;
    m_homeWidget->setContentsMargins(0, m_titlebar->height(), 0, 0);

    m_subStacksWidget = new QStackedWidget();//TODO:有时候导致主界面启动时还有一个小界面闪烁一下
    //m_subStacksWidget->setGeometry(this->rect());
    m_subStacksWidget->setContentsMargins(0, m_titlebar->height(), 0, 0);
    m_infoWidget = new InfoFrame;
    m_subStacksWidget->addWidget(m_infoWidget);
    m_monitorWidget = new MonitorFrame;
    m_subStacksWidget->addWidget(m_monitorWidget);
    m_cleanWidget = new CleanFrame;
    m_subStacksWidget->addWidget(m_cleanWidget);
    m_toolsWidget = new ToolsFrame;
    m_subStacksWidget->addWidget(m_toolsWidget);

    this->initEdgeWidget();

    m_rightPanel = new RightPanel(this);
    connect(m_rightPanel, &RightPanel::requestHide, this, &MainWindow::onHideRightPanel);
    m_rightPanel->setFixedSize(220, this->height() - m_titlebar->height());
//    m_rightPanel->move(this->width()-220, m_titlebar->height());
//    m_rightPanel->hide();
    QShortcut* sc = new QShortcut(QKeySequence("F3"), this);
    sc->setContext(Qt::WindowShortcut);
    connect(sc, &QShortcut::activated, this, [=] () {
        toggleRightPanel();
    });

    centralWidget = new QWidget;
    centralWidget->setObjectName("centerWidget");
    this->setCentralWidget(centralWidget);
    this->centralWidget->setMouseTracking(true);
    QStackedLayout *contentLayout = new QStackedLayout(centralWidget);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setMargin(0);
    contentLayout->setSpacing(0);
    contentLayout->addWidget(m_titlebar);
    contentLayout->addWidget(m_homeWidget);
    contentLayout->addWidget(m_subStacksWidget);
    contentLayout->addWidget(m_rightPanel);
    contentLayout->addWidget(m_edgeWidget);

    m_titlebar->show();
    m_homeWidget->show();

    QTimer::singleShot(1, this, &MainWindow::moveCenter);

    connect(m_homeWidget, &HomeWidget::requestBack, m_titlebar, &TopToolBar::setBackBtnVisible);
    connect(m_homeWidget, &HomeWidget::requestSubWidget, this, [=] (int index, const QString &name) {
        if (index < m_subStacksWidget->count()) {
            //给titlebar的中间区域设置一个label
            QWidget *w = new QWidget();
            QHBoxLayout *layout = new QHBoxLayout(w);
            layout->setContentsMargins(0, 0, 0, 0);
            layout->setSpacing(0);
            QLabel *textLabel = new QLabel;
            textLabel->setText(name);
            textLabel->setFixedSize(120, 24);
            layout->addStretch();
            layout->addWidget(textLabel);
            layout->addStretch();
            m_titlebar->setMiddleWidget(w);
            m_titlebar->setBackBtnVisible();

            if (index == 0) {
                QStringList types;
                types << "cpu" << "memory" << "disk" << "bios" << "motherboard" << "usb" << "vga" << "network";
                m_infoWidget->refreshWidgets(types);
            }
            else if (index == 1) {
//                m_monitorWidget->updateDatas();
            }

            m_subStacksWidget->setCurrentIndex(index);
            this->slideToSubWidgets();
        }
    });

    connect(m_titlebar, &TopToolBar::requestShowHomePage, this, [=] () {
        m_titlebar->setMiddleWidget(nullptr);
        m_homeWidget->showHomePage();
        this->slideToHomePage();
    });
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destory!!!";
    if (m_titlebar != nullptr) {
        delete m_titlebar;
        m_titlebar = nullptr;
    }
    if (m_rightPanel != nullptr) {
        delete m_rightPanel;
        m_rightPanel = nullptr;
    }
    if (m_edgeWidget != nullptr) {
        delete m_edgeWidget;
        m_edgeWidget = nullptr;
    }
    if (m_homeWidget != nullptr) {
        delete m_homeWidget;
        m_homeWidget = nullptr;
    }
    if (m_subStacksWidget) {
        foreach (QObject *child, m_subStacksWidget->children()) {
            QWidget *w = static_cast<QWidget *>(child);
            w->deleteLater();
        }
        delete m_subStacksWidget;
    }
    if (centralWidget != nullptr) {
        delete centralWidget;
        centralWidget = nullptr;
    }
}

//// 根据当前鼠标位置，定位鼠标在具体哪一块拉伸区域
//MainWindow::WindowStretchRectState MainWindow::getCurrentStretchState(QPoint cursorPos)
//{
//    WindowStretchRectState stretchState;
//    if (m_leftTopRect.contains(cursorPos))
//    {
//        stretchState = LEFT_TOP_RECT;
//    }
//    else if (m_rightTopRect.contains(cursorPos))
//    {
//        stretchState = RIGHT_TOP_RECT;
//    }
//    else if (m_rightBottomRect.contains(cursorPos))
//    {
//        stretchState = RIGHT_BOTTOM_RECT;
//    }
//    else if (m_leftBottomRect.contains(cursorPos))
//    {
//        stretchState = LEFT_BOTTOM_RECT;
//    }
//    else if (m_topBorderRect.contains(cursorPos))
//    {
//        stretchState = TOP_BORDER;
//    }
//    else if (m_rightBorderRect.contains(cursorPos))
//    {
//        stretchState = RIGHT_BORDER;
//    }
//    else if (m_bottomBorderRect.contains(cursorPos))
//    {
//        stretchState = BOTTOM_BORDER;
//    }
//    else if (m_leftBorderRect.contains(cursorPos))
//    {
//        stretchState = LEFT_BORDER;
//    }
//    else
//    {
//        stretchState = NO_SELECT;
//    }

//    return stretchState;
//}

//// 根据getCurrentStretchState返回状态进行更新鼠标样式;
//void MainWindow::updateMouseStyle(WindowStretchRectState stretchState)
//{
//    switch (stretchState)
//    {
//    case NO_SELECT:
//        setCursor(Qt::ArrowCursor);
//        break;
//    case LEFT_TOP_RECT:
//    case RIGHT_BOTTOM_RECT:
//        setCursor(Qt::SizeFDiagCursor);
//        break;
//    case TOP_BORDER:
//    case BOTTOM_BORDER:
//        setCursor(Qt::SizeVerCursor);
//        break;
//    case RIGHT_TOP_RECT:
//    case LEFT_BOTTOM_RECT:
//        setCursor(Qt::SizeBDiagCursor);
//        break;
//    case LEFT_BORDER:
//    case RIGHT_BORDER:
//        setCursor(Qt::SizeHorCursor);
//        break;
//    default:
//        setCursor(Qt::ArrowCursor);
//        break;
//    }
//}

void MainWindow::initEdgeWidget()
{
    m_edgeWidget = new ExtensionEdgeWidget(this);
    m_edgeWidget->setFixedHeight(this->height() - m_titlebar->height());
    m_edgeWidget->move(-m_edgeWidget->width(), 0);

    QShortcut* sc = new QShortcut(QKeySequence("Alt+Return"), this);
    sc->setContext(Qt::WindowShortcut);
    connect(sc, &QShortcut::activated, this, [=] () {
        if (m_edgeShowed) {
            // no with animation
            /*m_edgeShowed = false;
            m_edgeWidget->move(-m_edgeWidget->width(), 0);*/

            // with animation
            this->setEdgeWidgetVisible(false, false);
        }
        else {
            // no with animation
            /*m_edgeShowed = true;
            m_edgeWidget->move(0, 0);
            m_edgeWidget->setFocus();
            m_edgeWidget->show();
            m_edgeWidget->raise();*/

            // with animation
            this->setEdgeWidgetVisible(true, false);
        }
    });


    connect(m_edgeWidget, &ExtensionEdgeWidget::requestHide, this, [=] () {
        this->setEdgeWidgetVisible(false, false);
    });

}

void MainWindow::onHideRightPanel()
{
    this->setRightPanelVisible(false);
}

void MainWindow::toggleRightPanel()
{
    setRightPanelVisible(!m_rightPanel->isVisible());
}

void MainWindow::setRightPanelVisible(bool visible)
{
    if (m_rightPanel->isVisible() == visible) {
        if (visible) {
            m_rightPanel->setFocus();
            m_rightPanel->show();
            m_rightPanel->raise();
        }
        return;
    }

    if (m_rightPanel->property("moving").toBool()) {//上次动画还在运行中
        return;
    }

    m_rightPanel->setEnabled(false);
    m_rightPanel->setProperty("moving", true);
    int titleBarHeight = m_titlebar->height();

    if (!visible) {//隐藏
        QRect startRect(this->width() - m_rightPanel->width(), titleBarHeight, m_rightPanel->width(), m_rightPanel->height());
        QRect endRect(this->width(), titleBarHeight, m_rightPanel->width(), m_rightPanel->height());
        slideEdgeWidget(m_rightPanel, startRect, endRect, 500, true);
    }
    else {//显示
        QRect startRect(this->width(), titleBarHeight, m_rightPanel->width(), m_rightPanel->height());
        QRect endRect(this->width() - m_rightPanel->width(), titleBarHeight, m_rightPanel->width(), m_rightPanel->height());
        m_rightPanel->setFocus();
        slideEdgeWidget(m_rightPanel, startRect, endRect, 500, false);
        m_rightPanel->raise();
    }
    m_titlebar->raise();

    QTimer::singleShot(500, this, [=] { m_rightPanel->setProperty("moving", false); });
}

void MainWindow::setEdgeWidgetVisible(bool visible, bool immediately)
{
    if (visible) {
        m_edgeShowed = true;
        if (m_edgeWidget->x() == 0) {//已经处于显示状态了
            return;
        }

        if (this->window()->isFullScreen()) {
            m_edgeWidget->move(-qMax(m_edgeWidget->width(), EXTENSION_EDGE_WIDGET_WIDTH), 0);
            m_edgeWidget->moveWithAnimation(0, 0);
        }
        else {
            m_edgeWidget->move(-qMax(m_edgeWidget->width(), EXTENSION_EDGE_WIDGET_WIDTH), TOP_TOOLBAR_HEIGHT);
            m_edgeWidget->moveWithAnimation(0, TOP_TOOLBAR_HEIGHT);
        }

        m_edgeWidget->setFocus();
        m_edgeWidget->show();
        m_edgeWidget->raise();
    }
    else {
        m_edgeShowed = false;
        if (immediately) {
            m_edgeWidget->requestStopAnimation();
            if (this->window()->isFullScreen()) {
                m_edgeWidget->move(-qMax(m_edgeWidget->width(), EXTENSION_EDGE_WIDGET_WIDTH), 0);
            }
            else {
                m_edgeWidget->move(-qMax(m_edgeWidget->width(), EXTENSION_EDGE_WIDGET_WIDTH), TOP_TOOLBAR_HEIGHT);
            }
        }
        else {
            if (this->window()->isFullScreen()) {
                m_edgeWidget->moveWithAnimation(-qMax(m_edgeWidget->width(), EXTENSION_EDGE_WIDGET_WIDTH), 0);
            }
            else {
                m_edgeWidget->moveWithAnimation(-qMax(m_edgeWidget->width(), EXTENSION_EDGE_WIDGET_WIDTH), TOP_TOOLBAR_HEIGHT);
            }
        }
    }
}

void MainWindow::slideToSubWidgets()
{
    QWidget *current = m_currentWidget ? m_currentWidget : m_homeWidget;
    if (m_subStacksWidget->isVisible()) {
        m_currentWidget = m_subStacksWidget;
        m_subStacksWidget->raise();
        m_titlebar->raise();
        return;
    }

    switchWidgetFromBottomToTop(current, m_subStacksWidget, 500);
    this->update();
    m_currentWidget = m_subStacksWidget;
    m_titlebar->raise();
}

void MainWindow::slideToHomePage()
{
    QWidget *current = m_currentWidget ? m_currentWidget : m_subStacksWidget;
    if (m_homeWidget->isVisible()) {
        m_currentWidget = m_homeWidget;
        m_homeWidget->raise();
        m_titlebar->raise();
        return;
    }

    switchWidgetFromTopToBottom(current, m_homeWidget, 500);
    this->update();
    m_currentWidget = m_homeWidget;
    m_titlebar->raise();
}

void MainWindow::moveCenter()
{
    QPoint pos = QCursor::pos();
    QRect primaryGeometry;
    for (QScreen *screen : qApp->screens()) {
        if (screen->geometry().contains(pos)) {
            primaryGeometry = screen->geometry();
        }
    }

    if (primaryGeometry.isEmpty()) {
        primaryGeometry = qApp->primaryScreen()->geometry();
    }

    this->move(primaryGeometry.x() + (primaryGeometry.width() - this->width())/2, primaryGeometry.y() + (primaryGeometry.height() - this->height())/2);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_mousePress = true;
        m_movePoint = event->globalPos() - pos();
    }

    event->accept();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_mousePress = false;
    }

    event->accept();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QMainWindow::mouseMoveEvent(event);

    if (this->isMaximized() || this->isFullScreen()) {
        return;
    }

    if (m_mousePress) {
        QPoint movePpos = event->globalPos();
        move(movePpos - m_movePoint);
    }
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    QMainWindow::resizeEvent(e);
    QSize newSize = QMainWindow::size();

    if (m_titlebar) {
        this->m_titlebar->raise();
        this->m_titlebar->move(0, 0);
        this->m_titlebar->resize(newSize.width(), this->m_titlebar->height());
        if (e->oldSize() != e->size()) {
            emit m_titlebar->requestUpdateMaxBtn();
        }
    }

    if (m_edgeWidget) {
        m_edgeWidget->setFixedHeight(this->height() - m_titlebar->height());
    }

    this->m_homeWidget->resize(newSize);
    this->m_subStacksWidget->resize(newSize);

    this->m_rightPanel->setFixedSize(220, newSize.height() - m_titlebar->height());
    if (this->m_rightPanel->isVisible()) {
        this->m_rightPanel->hide();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "MainWindow closeEvent!!!";
    qApp->quit();
    event->accept();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QBitmap bitmap(this->size());
    bitmap.fill();
    QPainter painter(&bitmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawRoundedRect(bitmap.rect(), 6, 6);
    setMask(bitmap);
}
