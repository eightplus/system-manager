#include "monitorframe.h"
#include "monitorinterface.h"
#include "monitor/monitorworkerthread.h"
#include "monitor/monitorbasewidget.h"
#include "monitor/memorymonitor.h"
#include "monitor/cpumonitor.h"
#include "monitor/diskmonitor.h"
#include "monitor/iomonitor.h"
#include "monitor/networkmonitor.h"
#include "monitor/processmonitor.h"
#include "monitor/temperaturemonitor.h"
#include "monitor/processscrollareaframe.h"
#include "propertywidget.h"
#include "toolwidget.h"
#include "aboutwidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QVariant>
#include <QStackedWidget>
#include <QScrollArea>
#include <QTimer>
#include <QDebug>

static const char *selectedProperty         = "selected_state";
static const QString sValueSelected    = "selected";
static const QString sValueUnSelected      = "un_selected";


MonitorFrame::MonitorFrame(QWidget *parent) :
    QFrame(parent)
    , m_stackWidget(new QStackedWidget(this))
    , m_layout(new QHBoxLayout(this))
    , m_currentCatagary(MonitorButton::MonitorCatagary::Invalid)
    , m_moduleLoadDelay(0)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->initUI();

    this->updateDatas();
}

MonitorFrame::~MonitorFrame()
{
    if (m_stackWidget) {
        foreach (QObject *child, m_stackWidget->children()) {
            QWidget *w = static_cast<QWidget *>(child);
            w->deleteLater();
        }
        delete m_stackWidget;
    }

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

    qDeleteAll(m_modules_list.begin(), m_modules_list.end());
    m_modules_list.clear();

    qDeleteAll(m_moduleInterfaces.begin(), m_moduleInterfaces.end());
    m_moduleInterfaces.clear();
    //qDeleteAll(m_moduleInterfaces);
}

void MonitorFrame::initUI()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);

    this->initLeftContent();
    this->initRightContent();
}

void MonitorFrame::initLeftContent()
{
    QWidget *leftWidget = new QWidget;
    leftWidget->setFixedWidth(150);
    leftWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
//    leftWidget->setObjectName("LeftNavWidget");
//    leftWidget->setStyleSheet("#LeftNavWidget {border:solid #888888;border-right-width: 1px;}"
//                              "#LeftNavWidget > QPushButton {margin: 0;text-align: left;padding: 0px 15px;border: none;}"
//                              "#LeftNavWidget > QPushButton:checked {color: #ffffff;font-weight: 500;background-color: rgba(10,10,10,50);border: 1px solid rgba(255, 255, 255, .1);border-left: none;border-right: none;}");
    m_lLayout = new QVBoxLayout(leftWidget);
    m_lLayout->setContentsMargins(0, 0, 0, 0);
    m_lLayout->setSpacing(0);
    m_layout->addWidget(leftWidget, 0, Qt::AlignLeft);
}

void MonitorFrame::initRightContent()
{
    m_stackWidget->setContentsMargins(0, 0, 0, 0);
    QWidget *rightWidget = new QWidget;
    rightWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_rLayout = new QVBoxLayout(rightWidget);
    m_rLayout->setContentsMargins(0, 0, 6, 0);
    m_rLayout->setSpacing(0);
    m_layout->addWidget(rightWidget);
    m_rLayout->addWidget(m_stackWidget);
}

void MonitorFrame::refreshNavBar(const QStringList &types)
{
    /*
    // clear old widgets
    //去掉所有弹簧
    for (int i = 0; i < m_lLayout->count(); ++i) {
        QLayoutItem *layoutItem = m_lLayout->itemAt(i);
        if (layoutItem->spacerItem()) {
            m_lLayout->removeItem(layoutItem);
            --i;
        }
    }
//    while (m_lLayout->count()) {
//        m_lLayout->removeWidget(m_lLayout->itemAt(0)->widget());
//        m_lLayout->itemAt(0)->widget()->setParent(nullptr);
//    }
    QLayoutItem *child;
    while ((child = m_lLayout->takeAt(0)) != 0) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    qDeleteAll(m_modules_list.begin(), m_modules_list.end());
    m_modules_list.clear();

    // add new widgets
    int index = 0;
    foreach (const QString &name, types) {
        MonitorButton *btn = new MonitorButton;
        if (name == "process") {
            btn->setIconAndtext(MonitorButton::MonitorCatagary::Process, ":/res/tool.png", name);
        }
        else if (name == "network") {
            btn->setIconAndtext(MonitorButton::MonitorCatagary::Resource, ":/res/tool.png", name);
        }
        else if (name == "io") {
            btn->setIconAndtext(MonitorButton::MonitorCatagary::Sysfile, ":/res/tool.png", name);
        }
        if (index == 0)
            btn->updateQssProperty(selectedProperty, sValueSelected);
        else
            btn->updateQssProperty(selectedProperty, sValueUnSelected);
        connect(btn, &MonitorButton::clicked, this, &MonitorFrame::onMonitorButtonClicked);
        m_modules_list.push_back(btn);
        m_lLayout->addWidget(btn, 0, Qt::AlignLeft | Qt::AlignVCenter);
        index ++;
    }
    if (index > 0) {
        m_lLayout->addStretch();
    }
*/












    /*
    MonitorButton *processBtn = new MonitorButton;
    processBtn->setIconAndtext(MonitorButton::MonitorCatagary::Process, ":/res/tool.png", tr("Process"));
    processBtn->updateQssProperty(selectedProperty, sValueSelected);
    connect(processBtn, &MonitorButton::clicked, this, &MonitorFrame::onMonitorButtonClicked);
    m_modules_list.push_back(processBtn);
    m_lLayout->addWidget(processBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);

    MonitorButton *resourceBtn = new MonitorButton;
    resourceBtn->setIconAndtext(MonitorButton::MonitorCatagary::Resource, ":/res/tool.png", tr("Resource"));
    resourceBtn->updateQssProperty(selectedProperty, sValueUnSelected);
    connect(resourceBtn, &MonitorButton::clicked, this, &MonitorFrame::onMonitorButtonClicked);
    m_modules_list.push_back(resourceBtn);
    m_lLayout->addWidget(resourceBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);

    MonitorButton *sysfileBtn = new MonitorButton;
    sysfileBtn->setIconAndtext(MonitorButton::MonitorCatagary::Sysfile, ":/res/tool.png", tr("Sysfile"));
    sysfileBtn->updateQssProperty(selectedProperty, sValueUnSelected);
    connect(sysfileBtn, &MonitorButton::clicked, this, &MonitorFrame::onMonitorButtonClicked);
    m_modules_list.push_back(sysfileBtn);
    m_lLayout->addWidget(sysfileBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);

    MonitorButton *ioBtn = new MonitorButton;
    ioBtn->setIconAndtext(MonitorButton::MonitorCatagary::IO, ":/res/tool.png", tr("IO"));
    ioBtn->updateQssProperty(selectedProperty, sValueUnSelected);
    connect(ioBtn, &MonitorButton::clicked, this, &MonitorFrame::onMonitorButtonClicked);
    m_modules_list.push_back(ioBtn);
    m_lLayout->addWidget(ioBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);

    m_lLayout->addStretch();
    */
}

void MonitorFrame::refreshWidgets(const QStringList &types)
{
    /*
    // clear old widgets
    while (m_stackWidget->count() > 0) {
        QWidget *w = m_stackWidget->widget(0);
        if (w != nullptr) {
            w->setParent(NULL);
            m_stackWidget->removeWidget(w);
            w->deleteLater();//delete w;
        }
    }

    // add new widgets
    foreach (const QString &name, types) {
        if (name == "process") {
            ProcessScrollAreaFrame *m_procFrame = new ProcessScrollAreaFrame;
            m_stackWidget->addWidget(m_procFrame);
            m_modules_map.insert(MonitorButton::MonitorCatagary::Process, m_procFrame);
        }
        else if (name == "network") {
            PropertyWidget *propertyWidget = new PropertyWidget;
            m_stackWidget->addWidget(propertyWidget);
            m_modules_map.insert(MonitorButton::MonitorCatagary::Resource, propertyWidget);
        }
        else if (name == "io") {
            ToolWidget *toolWidget = new ToolWidget;
            m_stackWidget->addWidget(toolWidget);
            m_modules_map.insert(MonitorButton::MonitorCatagary::Sysfile, toolWidget);
        }
    }
    m_stackWidget->setCurrentIndex(0);
    connect(m_stackWidget, &QStackedWidget::currentChanged, this, [=] (int i) {
//        if (m_stackWidget->m_currentWidget() == m_procFrame) {

//        }
    });
    m_rLayout->addWidget(m_stackWidget);
    */



    /*
    ProcessScrollAreaFrame *m_procFrame = new ProcessScrollAreaFrame(this);
    PropertyWidget *propertyWidget = new PropertyWidget(this);
    ToolWidget *toolWidget = new ToolWidget(this);
    AboutWidget *aboutWidget = new AboutWidget(this);

    m_stackWidget->addWidget(m_procFrame);
    m_modules_map.insert(MonitorButton::MonitorCatagary::Process, m_procFrame);

    m_stackWidget->addWidget(propertyWidget);
    m_modules_map.insert(MonitorButton::MonitorCatagary::Resource, propertyWidget);

    m_stackWidget->addWidget(toolWidget);
    m_modules_map.insert(MonitorButton::MonitorCatagary::Sysfile, toolWidget);

    m_stackWidget->addWidget(aboutWidget);
    m_modules_map.insert(MonitorButton::MonitorCatagary::IO, aboutWidget);

    m_stackWidget->setContentsMargins(0, 0, 0, 0);

    m_stackWidget->setCurrentIndex(0);
    connect(m_stackWidget, &QStackedWidget::currentChanged, this, [=] (int i) {

//        if (m_stackWidget->m_currentWidget() == m_procFrame) {

//        }
    });

    m_rLayout->addWidget(m_stackWidget);
    */
}

void MonitorFrame::addNavigationItem(const QString &name, bool first)
{
    MonitorButton *btn = new MonitorButton;
    if (name == "memory monitor") {
        btn->setIconAndtext(MonitorButton::MonitorCatagary::Memory, ":/res/tool.png", name);
    }
    else if (name == "cpu monitor") {
        btn->setIconAndtext(MonitorButton::MonitorCatagary::Cpu, ":/res/tool.png", name);
    }
    else if (name == "disk monitor") {
        btn->setIconAndtext(MonitorButton::MonitorCatagary::Disk, ":/res/tool.png", name);
    }
    else if (name == "io monitor") {
        btn->setIconAndtext(MonitorButton::MonitorCatagary::IO, ":/res/tool.png", name);
    }
    else if (name == "network monitor") {
        btn->setIconAndtext(MonitorButton::MonitorCatagary::Network, ":/res/tool.png", name);
    }
    else if (name == "process monitor") {
        btn->setIconAndtext(MonitorButton::MonitorCatagary::Process, ":/res/tool.png", name);
    }
    else if (name == "temperature monitor") {
        btn->setIconAndtext(MonitorButton::MonitorCatagary::Temperature, ":/res/tool.png", name);
    }
    else {//TODO:如果存在多个Invalid，将导致异常
        btn->setIconAndtext(MonitorButton::MonitorCatagary::Invalid, ":/res/tool.png", name);
    }

    if (first)
        btn->updateQssProperty(selectedProperty, sValueSelected);
    else
        btn->updateQssProperty(selectedProperty, sValueUnSelected);
    connect(btn, &MonitorButton::clicked, this, &MonitorFrame::onMonitorButtonClicked);
    m_modules_list.push_back(btn);
    m_lLayout->addWidget(btn, 0, Qt::AlignLeft | Qt::AlignVCenter);
}

void MonitorFrame::updateDatas()
{
//    QStringList list;
//    list << "process" << "network" << "io";
//    this->refreshNavBar(list);
//    this->refreshWidgets(list);


    // clear old widgets
    //去掉所有弹簧
    for (int i = 0; i < m_lLayout->count(); ++i) {
        QLayoutItem *layoutItem = m_lLayout->itemAt(i);
        if (layoutItem->spacerItem()) {
            m_lLayout->removeItem(layoutItem);
            --i;
        }
    }
//    while (m_lLayout->count()) {
//        m_lLayout->removeWidget(m_lLayout->itemAt(0)->widget());
//        m_lLayout->itemAt(0)->widget()->setParent(nullptr);
//    }
    QLayoutItem *child;
    while ((child = m_lLayout->takeAt(0)) != 0) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    qDeleteAll(m_modules_list.begin(), m_modules_list.end());
    m_modules_list.clear();

    // clear old widgets
    while (m_stackWidget->count() > 0) {
        QWidget *w = m_stackWidget->widget(0);
        if (w != nullptr) {
            w->setParent(NULL);
            m_stackWidget->removeWidget(w);
            w->deleteLater();//delete w;
        }
    }

    loadModule(new MemoryMonitor(this));
    loadModule(new CpuMonitor(this));
    loadModule(new DiskMonitor(this));
    loadModule(new IoMonitor(this));
    loadModule(new NetworkMonitor(this));
    loadModule(new ProcessMonitor(this));
    loadModule(new TemperatureMonitor(this));
}

void MonitorFrame::loadModule(MonitorInterface *const module)
{
    Q_ASSERT(!m_moduleInterfaces.contains(module));
    m_moduleInterfaces.append(module);

    MonitorWorkerThread *thrd = new MonitorWorkerThread(module, this);
    connect(thrd, &MonitorWorkerThread::moduleInitFinished, this, &MonitorFrame::onModuleInitFinished, Qt::QueuedConnection);
    connect(thrd, &MonitorWorkerThread::finished, thrd, &MonitorWorkerThread::deleteLater, Qt::QueuedConnection);


    const QString name = module->name();
    if (name == "memory monitor") {
        this->addNavigationItem(name, true);
        return thrd->start(QThread::HighestPriority);
    }
    else {
        this->addNavigationItem(name, false);
    }

    QTimer::singleShot(m_moduleLoadDelay, thrd, [=] { thrd->start(QThread::LowestPriority); });

    m_moduleLoadDelay += 50;
    m_moduleLoadDelay %= 340;
}

void MonitorFrame::onModuleInitFinished(MonitorInterface *const module)
{
    Q_ASSERT(m_moduleInterfaces.contains(module));

    MonitorBaseWidget *moduleWidget = module->moduleWidget();
    m_moduleActivable[module] = false;
    m_stackWidget->addWidget(moduleWidget);

    // load all monitors finished
    if (m_moduleActivable.size() == m_moduleInterfaces.size()) {
        m_lLayout->addStretch();
        QTimer::singleShot(10, this, [=] { m_stackWidget->setCurrentIndex(0); });
    }
}

void MonitorFrame::onMonitorButtonClicked(MonitorButton::MonitorCatagary catagary)
{
    if (m_currentCatagary == catagary) {
        return;
    }

    m_currentCatagary = catagary;

    QString name = "";
    if (catagary == MonitorButton::MonitorCatagary::Memory) {
        name = "memory monitor";
    }
    else if (catagary == MonitorButton::MonitorCatagary::Cpu) {
        name = "cpu monitor";
    }
    else if (catagary == MonitorButton::MonitorCatagary::Disk) {
        name = "disk monitor";
    }
    else if (catagary == MonitorButton::MonitorCatagary::IO) {
        name = "io monitor";
    }
    else if (catagary == MonitorButton::MonitorCatagary::Network) {
        name = "network monitor";
    }
    else if (catagary == MonitorButton::MonitorCatagary::Process) {
        name = "process monitor";
    }
    else if (catagary == MonitorButton::MonitorCatagary::Temperature) {
        name = "temperature monitor";
    }


    //qDebug() << "m_modules_list len:" << m_modules_list.length();
    foreach (MonitorButton *btn, m_modules_list) {
        if (btn->getCatagary() == catagary) {
            btn->updateQssProperty(selectedProperty, sValueSelected);
        }
        else {
            btn->updateQssProperty(selectedProperty, sValueUnSelected);
        }
    }

    //scrollArea->verticalScrollBar()->setValue(0);

    MonitorInterface *inter = nullptr;
    for (auto it : m_moduleInterfaces) {
        if (it->name() == name) {
            inter = it;
            break;
        }
    }

    if (inter) {
        QWidget *w = inter->moduleWidget();
        m_stackWidget->setCurrentWidget(w);
    }


    //m_stackWidget->setCurrentWidget(m_modules_map.value(catagary));
}
