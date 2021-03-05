#include "memorywidget.h"
#include "protest1.h"
#include "protest2.h"

#include <QPushButton>
#include <QDebug>
#include <QStackedWidget>

MemoryWidget::MemoryWidget()
    : MonitorBaseWidget()
    , m_btn(new QPushButton(tr("Test")))
{
    setObjectName("Memory");

    m_centralLayout->addWidget(m_btn);

    setTitle(tr("Memory Monitor"));


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
