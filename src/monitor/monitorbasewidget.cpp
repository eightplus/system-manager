#include "monitorbasewidget.h"

#include <QEvent>
#include <QLabel>
#include <QDebug>
#include <QStackedWidget>
#include <QScrollBar>
#include <QScrollArea>
#include <QScroller>
#include <QPropertyAnimation>
#include <QWheelEvent>

MonitorBaseWidget::MonitorBaseWidget()
    : QWidget(nullptr)
{
    m_moduleIcon = new QLabel;
    m_moduleIcon->setFixedSize(24, 24);

    m_moduleTitle = new QLabel;
    m_moduleTitle->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    m_moduleTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QWidget *titleFrame = new QWidget;
    titleFrame->setObjectName("whiteWidget");
    titleFrame->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *titleLayout = new QHBoxLayout(titleFrame);
    //QHBoxLayout *titleLayout = new QHBoxLayout;titleFrame->setLayout(titleLayout);
    titleLayout->setSpacing(0);
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleLayout->addWidget(m_moduleIcon);
    titleLayout->setAlignment(m_moduleIcon, Qt::AlignCenter);
    titleLayout->addWidget(m_moduleTitle);



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

    m_centralLayout = new QVBoxLayout;
    m_centralLayout->addWidget(titleFrame);
    m_centralLayout->addWidget(m_stackWidget);
    m_centralLayout->setContentsMargins(0, 0, 0, 0);
    m_centralLayout->setSpacing(0);
    m_centralLayout->setMargin(0);

    this->setLayout(m_centralLayout);
}


MonitorBaseWidget::~MonitorBaseWidget()
{
    qDebug() << "MonitorBaseWidget destroy!!!";

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

    //No.3: delete m_centralLayout
    while ((child = m_centralLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
}

const QString MonitorBaseWidget::title() const
{
    return m_moduleTitle->text();
}

void MonitorBaseWidget::setTitle(const QString &title)
{
    m_moduleTitle->setText(title);

    setAccessibleName(title);
}

void MonitorBaseWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_area->verticalScrollBar()->setVisible(true);
}

void MonitorBaseWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_area->verticalScrollBar()->setVisible(false);
}
