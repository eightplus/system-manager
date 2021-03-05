#include "toolsframe.h"
#include "navigationbutton.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QDebug>

#define NAVIGATION_WIDTH 150
#define NAVIGATION_HEIGHT 36


ToolsFrame::ToolsFrame(QWidget *parent) :
    QFrame(parent)
  , m_pluginLoader(new PluginLoader(this))
  , m_stackedLayout(new QStackedLayout)
  , m_navButtonsGroup(new QButtonGroup)
  , m_layout(new QHBoxLayout(this))
  , m_currentIndex(-1)
{
    m_stackedLayout->setMargin(0);
    m_stackedLayout->setSpacing(0);
    m_navButtonsGroup->setExclusive(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->initUI();

    connect(m_pluginLoader, &PluginLoader::pluginAdded, this, &ToolsFrame::pluginAdded, Qt::QueuedConnection);
    m_pluginLoader->loadPlugins();
}

ToolsFrame::~ToolsFrame()
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

    while ((child = m_layout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

//    qDeleteAll(m_navButtonsGroup->children());
    for (QAbstractButton* button : m_navButtonsGroup->buttons()) {
        m_navButtonsGroup->removeButton(button);
    }
}


void ToolsFrame::pluginAdded(QWidget * const w, const QString &name)
{
    if (w) {
        w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        const int idx = m_stackedLayout->addWidget(w);
        const int count = m_stackedLayout->count();
        m_stackedLayout->setCurrentIndex(idx);

        qDebug() << "ToolsFrame::pluginAdded: " << name;
        QPushButton *btn = new NavigationButton(NavigationButton::FringePosition::Left);
        btn->setText(name);
        btn->setFixedSize(NAVIGATION_WIDTH, NAVIGATION_HEIGHT);
        m_lLayout->addWidget(btn, 0, Qt::AlignLeft | Qt::AlignVCenter);
        m_navButtonsGroup->addButton(btn);
        connect(btn, &QPushButton::clicked, this, [=] { onNavButtonClicked(count-1); });
    }
    else {
        if (name == "over") {
            m_lLayout->addStretch();
            m_navButtonsGroup->buttons().first()->click();
        }
    }
}


void ToolsFrame::initUI()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);

    this->initLeftContent();
    this->initRightContent();

//    m_navButtonsGroup->buttons().first()->click();

//    for (QAbstractButton* button : m_navButtonsGroup->buttons()) {
//        QPushButton* btn = qobject_cast<QPushButton*>(button);
//        if (btn == nullptr) {
//        }
//    }
}

void ToolsFrame::initLeftContent()
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

void ToolsFrame::setNavgationEnabled(const bool enabled)
{
    for (auto *button : m_navButtonsGroup->buttons()) {
        button->setEnabled(enabled);
    }
}

void ToolsFrame::onNavButtonClicked(int index)
{
   if (index == m_currentIndex) return;

   if (index > -1 && index < m_stackedLayout->count()) {
       m_currentIndex = index;
       m_stackedLayout->setCurrentIndex(index);
   }
}

void ToolsFrame::initRightContent()
{
    m_stackedLayout->setContentsMargins(0, 0, 0, 0);
    m_stackedLayout->setSpacing(0);

    // clear old widgets
    QLayoutItem *child;
    while ((child = m_stackedLayout->takeAt(0)) != 0) {
        QWidget *w = child->widget();
        if (w) {
            w->setParent(NULL);
            m_stackedLayout->removeWidget(w);
            w->deleteLater();
        }
        delete child;
    }

    QWidget *rightWidget = new QWidget;
    rightWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_rLayout = new QVBoxLayout(rightWidget);//rightWidget->setLayout(m_rLayout);
    m_rLayout->setContentsMargins(0, 0, 6, 0);
    m_rLayout->setSpacing(0);
    m_layout->addWidget(rightWidget);//m_layout->addWidget(rightWidget, 1, Qt::AlignLeft);//将导致m_stackWidget下所有界面缩放根据窗口大小自动缩放
    m_rLayout->addLayout(m_stackedLayout);
}
