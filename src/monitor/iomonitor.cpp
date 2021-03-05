#include "iomonitor.h"

IoMonitor::IoMonitor(QObject *parent)
    : QObject(parent),
      m_ioWidget(nullptr)
{
}

void IoMonitor::initialize()
{

}

void IoMonitor::reset()
{

}

MonitorBaseWidget *IoMonitor::moduleWidget()
{
    if (!m_ioWidget) {
        m_ioWidget = new IoWidget;
    }

    return m_ioWidget;
}

const QString IoMonitor::name() const
{
    return QStringLiteral("io monitor");
}

IoMonitor::~IoMonitor()
{

}
