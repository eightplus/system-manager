#include "diskmonitor.h"

DiskMonitor::DiskMonitor(QObject *parent)
    : QObject(parent),
      m_diskWidget(nullptr)
{
}

void DiskMonitor::initialize()
{

}

void DiskMonitor::reset()
{

}

MonitorBaseWidget *DiskMonitor::moduleWidget()
{
    if (!m_diskWidget) {
        m_diskWidget = new DiskWidget;
    }

    return m_diskWidget;
}

const QString DiskMonitor::name() const
{
    return QStringLiteral("disk monitor");
}

DiskMonitor::~DiskMonitor()
{

}
