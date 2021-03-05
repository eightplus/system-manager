#include "memorymonitor.h"

MemoryMonitor::MemoryMonitor(QObject *parent)
    : QObject(parent),
      m_memoryWidget(nullptr)
{
}

void MemoryMonitor::initialize()
{

}

void MemoryMonitor::reset()
{

}

MonitorBaseWidget *MemoryMonitor::moduleWidget()
{
    if (!m_memoryWidget) {
        m_memoryWidget = new MemoryWidget;
    }

    return m_memoryWidget;
}

const QString MemoryMonitor::name() const
{
    return QStringLiteral("memory monitor");
}

MemoryMonitor::~MemoryMonitor()
{

}
