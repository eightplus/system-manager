#include "processscrollareaframe.h"
#include "protest1.h"
#include "protest2.h"

#include <QCursor>
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QScrollBar>
#include <QDebug>

ProcessScrollAreaFrame::ProcessScrollAreaFrame(QWidget *parent)
    : BaseScrollWidget(parent)
{
    setTitle(tr("Process Page"));

    // Empty frame
    QLabel *errPage = new QLabel(tr("Error Page"));
    errPage->setAlignment(Qt::AlignCenter);
    errPage->setObjectName("ErroFrame");

    m_stackWidget->insertWidget(0, errPage);
    m_stackWidget->setCurrentIndex(1);


    ProFrame1 *frame1 = new ProFrame1(this);
    ProFrame2 *frame2 = new ProFrame2(this);
    areaLayout->addWidget(frame1);
    areaLayout->addWidget(frame2);
    areaLayout->addStretch();
}

ProcessScrollAreaFrame::~ProcessScrollAreaFrame()
{
    qDebug() << "ProcessScrollAreaFrame destory!!!";
}

/*const */QString ProcessScrollAreaFrame::title()/* const*/
{
    return m_titleLabel->text();
}

void ProcessScrollAreaFrame::setTitle(const QString &title)
{
    m_titleLabel->setText(title);
    setAccessibleName(title);
}

//ProcessScrollAreaFrame::ProcessScrollAreaFrame(QWidget *parent)
//    : QWidget(parent)
//{
//    m_layout = new QVBoxLayout(this);
//    m_layout->setContentsMargins(0, 0, 0, 0);
//    m_layout->setSpacing(0);

//    QLabel *label = new QLabel;
//    label->setText("Test Process");
//    QWidget *titleFrame = new QWidget;
//    titleFrame->setObjectName("whiteWidget");
//    titleFrame->setContentsMargins(0, 0, 0, 0);
//    QHBoxLayout *hlayout = new QHBoxLayout(titleFrame);
//    hlayout->setContentsMargins(0, 3, 3, 0);
//    hlayout->setSpacing(0);
//    hlayout->addWidget(label);
//    hlayout->addStretch();
//    m_layout->addWidget(titleFrame);

//    initScrollArea();
//}

//void ProcessScrollAreaFrame::initScrollArea()
//{
//    // Empty frame
//    QLabel *errPage = new QLabel(tr("Error Page"));
//    errPage->setAlignment(Qt::AlignCenter);
//    errPage->setObjectName("ErroFrame");

//    m_area = new QScrollArea;
//    m_area->setWidgetResizable(true);
//    m_area->setContentsMargins(0, 0, 0, 0);
//    m_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    //m_area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    //m_area->setFrameStyle(QFrame::NoFrame);

//    QScrollBar *sb = new QScrollBar();
//    m_area->setVerticalScrollBar(sb);
//    sb->setContextMenuPolicy(Qt::PreventContextMenu);

//    QWidget *areaContent = new QWidget;
//    areaContent->setObjectName("whiteWidget");
//    QVBoxLayout *layout = new QVBoxLayout(areaContent);
//    layout->setContentsMargins(0, 0, 0, 0);
//    layout->setSpacing(0);

//    ProFrame1 *frame1 = new ProFrame1(this);
//    ProFrame2 *frame2 = new ProFrame2(this);
//    layout->addWidget(frame1);
//    layout->addWidget(frame2);
//    layout->addStretch();
//    m_area->setWidget(areaContent);

//    m_stackWidget = new QStackedWidget;
//    m_stackWidget->setContentsMargins(0, 0, 0, 0);
//    m_stackWidget->addWidget(errPage);
//    m_stackWidget->addWidget(m_area);
//    m_stackWidget->setCurrentIndex(1);

//    m_layout->addWidget(m_stackWidget);
//}
