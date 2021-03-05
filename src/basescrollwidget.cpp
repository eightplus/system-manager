#include "basescrollwidget.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QScrollBar>
#include <QScrollArea>
#include <QScroller>
#include <QPropertyAnimation>
#include <QWheelEvent>
#include <QDebug>

BaseScrollWidget::BaseScrollWidget(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QVBoxLayout(this))
{
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    m_layout->setMargin(0);

    m_titleLabel = new QLabel;
    m_titleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QWidget *titleFrame = new QWidget;
    titleFrame->setObjectName("whiteWidget");
    titleFrame->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *titleLayout = new QHBoxLayout(titleFrame);
    //QHBoxLayout *titleLayout = new QHBoxLayout;titleFrame->setLayout(titleLayout);
    titleLayout->setSpacing(0);
    titleLayout->setContentsMargins(5, 0, 0, 0);
    titleLayout->addWidget(m_titleLabel);
    m_layout->addWidget(titleFrame);


    m_area = new QScrollArea;
    m_area->setWidgetResizable(true);
    m_area->setContentsMargins(0, 0, 0, 0);
    m_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //m_area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //m_area->setFrameStyle(QFrame::NoFrame);
//    QScroller::grabGesture(m_displayScrollArea, m_touch ? QScroller::TouchGesture : QScroller::LeftMouseButtonGesture);//QScroller::LeftMouseButtonGesture设置鼠标左键拖动，导致滚动条不能拖动
    QScroller::grabGesture(m_area->viewport(), QScroller::LeftMouseButtonGesture);

    QScrollBar *sb = new QScrollBar();
    m_area->setVerticalScrollBar(sb);
    sb->setContextMenuPolicy(Qt::PreventContextMenu);

    QWidget *areaContent = new QWidget;
    areaContent->setObjectName("whiteWidget");
    areaLayout = new QVBoxLayout(areaContent);
    areaLayout->setContentsMargins(0, 0, 0, 0);
    areaLayout->setSpacing(0);

    m_area->setWidget(areaContent);

    m_stackWidget = new QStackedWidget;
    m_stackWidget->setContentsMargins(0, 0, 0, 0);
    m_stackWidget->addWidget(m_area);

    m_layout->addWidget(m_stackWidget);

    this->setLayout(m_layout);
}

BaseScrollWidget::~BaseScrollWidget()
{
    qDebug() << "BaseScrollWidget destroy!!!";

    //delete all widgets
    //No.1: delete areaLayout
    QLayoutItem *child;
    while ((child = areaLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

    //No.2: delete m_stackWidget
    if (m_stackWidget) {
        foreach (QObject *child, m_stackWidget->children()) {
            QWidget *w = static_cast<QWidget *>(child);
            w->deleteLater();
        }
        delete m_stackWidget;
    }

    //No.3: delete m_layout
    while ((child = m_layout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
}

void BaseScrollWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_area->verticalScrollBar()->setVisible(true);
}

void BaseScrollWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_area->verticalScrollBar()->setVisible(false);
}
