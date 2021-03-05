#include "infoframe.h"
#include "info/infoscrollpanel.h"
#include "info/deviceframe1.h"
#include "info/deviceframe2.h"
#include "info/deviceframe3.h"
#include "navigationbutton.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QDebug>

#define NAVIGATION_WIDTH 150
#define NAVIGATION_HEIGHT 36

InfoFrame::InfoFrame(QWidget *parent) :
    QFrame(parent)
  , m_stackWidget(new QStackedWidget(this))
  , m_stackedLayout(new QStackedLayout)
  , m_navButtonsGroup(new QButtonGroup)
  , m_layout(new QHBoxLayout(this))
  , m_index(-1)
{
//    m_navButtonsGroup->setExclusive(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->initUI();
}

InfoFrame::~InfoFrame()
{
    QLayoutItem *child;
    while ((child = m_lLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

    while ((child = m_rLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

//    qDeleteAll(m_navButtonsGroup->children());
    for (QAbstractButton* button : m_navButtonsGroup->buttons()) {
        m_navButtonsGroup->removeButton(button);
    }
}

void InfoFrame::initUI()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);

    this->initLeftContent();
    this->initRightContent();

    for (QAbstractButton* button : m_navButtonsGroup->buttons()) {
        QPushButton* btn = qobject_cast<QPushButton*>(button);
        if (btn == nullptr) {
        }
    }
}

void InfoFrame::initLeftContent()
{
    QWidget *leftWidget = new QWidget;
    leftWidget->setFixedWidth(150);
    leftWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    leftWidget->setObjectName("LeftNavWidget");
    leftWidget->setStyleSheet("#LeftNavWidget {border:solid #888888;border-right-width: 1px;}"
                              "#LeftNavWidget > QPushButton {margin: 0;text-align: left;padding: 0px 15px;border: none;}"
                              "#LeftNavWidget > QPushButton:checked {color: #ffffff;font-weight: 500;background-color: rgba(10,10,10,50);border: 1px solid rgba(255, 255, 255, .1);border-left: none;border-right: none;}");
    m_lLayout = new QVBoxLayout(leftWidget);
    m_lLayout->setContentsMargins(0, 0, 0, 0);
    m_lLayout->setSpacing(0);
    m_layout->addWidget(leftWidget, 0, Qt::AlignLeft);
}


void InfoFrame::initRightContent()
{
    m_stackedLayout->setContentsMargins(0, 0, 0, 0);
    m_stackedLayout->setSpacing(0);

    QWidget *rightWidget = new QWidget;
    rightWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_rLayout = new QVBoxLayout(rightWidget);//rightWidget->setLayout(m_rLayout);
    m_rLayout->setContentsMargins(0, 0, 6, 0);
    m_rLayout->setSpacing(0);
    m_rLayout->addLayout(m_stackedLayout);

    m_layout->addWidget(rightWidget);//m_layout->addWidget(rightWidget, 1, Qt::AlignLeft);//将导致m_stackWidget下所有界面缩放根据窗口大小自动缩放
}

void InfoFrame::refreshWidgets(const QStringList &types)
{
    // clear old navigation buttons
    for (QAbstractButton* button : m_navButtonsGroup->buttons()) {
        m_navButtonsGroup->removeButton(button);
    }
    // 去掉所有弹簧
    for (int i = 0; i < m_lLayout->count(); ++i) {
        QLayoutItem *layoutItem = m_lLayout->itemAt(i);
        if (layoutItem->spacerItem()) {
            m_lLayout->removeItem(layoutItem);
            --i;
        }
    }
    QLayoutItem *child;
    while ((child = m_lLayout->takeAt(0)) != 0) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    // clear old content widgets
    while ((child = m_stackedLayout->takeAt(0)) != 0) {
        QWidget *w = child->widget();
        if (w) {
            w->setParent(NULL);
            m_stackedLayout->removeWidget(w);
            w->deleteLater();
        }
        delete child;
    }

    // add new navigation buttons and content widgets
    for (int i=0; i < types.length(); i++) {
        QPushButton *btn = new NavigationButton(NavigationButton::FringePosition::Left);
        btn->setText(types.at(i));
        btn->setFixedSize(NAVIGATION_WIDTH, NAVIGATION_HEIGHT);
        m_lLayout->addWidget(btn, 0, Qt::AlignLeft | Qt::AlignVCenter);
        m_navButtonsGroup->addButton(btn);
        connect(btn, &QPushButton::clicked, this, [=] { onNavButtonClicked(i); });

        InfoScrollPanel *scrollPanel = new InfoScrollPanel();
        scrollPanel->setTitle(types.at(i));
        DeviceFrame1 *frame1 = new DeviceFrame1();
        DeviceFrame2 *frame2 = new DeviceFrame2();
        DeviceFrame3 *frame3 = new DeviceFrame3();
        scrollPanel->addContentWidget(frame1);
        scrollPanel->addContentWidget(frame2);
        scrollPanel->addContentWidget(frame3);
        m_stackedLayout->addWidget(scrollPanel);
    }
    m_lLayout->addStretch();
    m_stackedLayout->setCurrentIndex(0);
//    m_navButtonsGroup->setExclusive(true);
    m_navButtonsGroup->buttons().first()->click();
}

void InfoFrame::setNavgationEnabled(const bool enabled)
{
    for (auto *button : m_navButtonsGroup->buttons()) {
        button->setEnabled(enabled);
    }
}

 void InfoFrame::onNavButtonClicked(const int index)
 {
     /*if (index == m_index) return;

     m_index = index;
     m_stackWidget->setCurrentIndex(m_index);*/


     QPushButton *button = qobject_cast<QPushButton*>(sender());
     Q_ASSERT(button);

    if (index == m_index) return;

    if (index < m_stackedLayout->count()) {
        m_index = index;
        m_stackedLayout->setCurrentIndex(m_index);
    }
}
