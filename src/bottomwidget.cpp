#include "bottomwidget.h"

#include <QHBoxLayout>
#include <QPushButton>

BottomWidget::BottomWidget(QWidget *parent) :
    QWidget(parent)
{
//    this->setObjectName("bottomWidget");
//    this->setStyleSheet("QWidget#bottomWidget{background:white;}");//background-color: #E4E7EA;
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(Qt::white));//"#0d87ca"
    this->setPalette(palette);

    this->initUI();
    this->initConnect();
}

void BottomWidget::initUI()
{
    m_infoButton = new QPushButton(this);
    m_infoButton->setObjectName("btnInfo");
    m_infoButton->setFixedSize(120, 200);
    m_infoButton->setText("Info");

    m_monitorButton = new QPushButton(this);
    m_monitorButton->setObjectName("btnMonitor");
    m_monitorButton->setFixedSize(120, 200);
    m_monitorButton->setText("Monitor");

    m_cleanButton = new QPushButton(this);
    m_cleanButton->setObjectName("btnClean");
    m_cleanButton->setFixedSize(120, 200);
    m_cleanButton->setText("Cleaner");

    m_toolsButton = new QPushButton(this);
    m_toolsButton->setObjectName("btnTools");
    m_toolsButton->setFixedSize(120, 200);
    m_toolsButton->setText("Tools");

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_infoButton);
    mainLayout->addWidget(m_monitorButton);
    mainLayout->addWidget(m_cleanButton);
    mainLayout->addWidget(m_toolsButton);
    mainLayout->addStretch();
    mainLayout->setContentsMargins(10, 20, 10, 10);

    this->setLayout(mainLayout);
}

void BottomWidget::initConnect()
{
    connect(m_infoButton, SIGNAL(clicked(bool)), this, SIGNAL(infoBtnClicked()));
    connect(m_monitorButton, SIGNAL(clicked(bool)), this, SIGNAL(monitorBtnClicked()));
    connect(m_cleanButton, SIGNAL(clicked(bool)), this, SIGNAL(cleanBtnClicked()));
    connect(m_toolsButton, SIGNAL(clicked(bool)), this, SIGNAL(toolsBtnClicked()));
}
