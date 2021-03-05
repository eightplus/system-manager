#include "cpumonitor.h"

CpuMonitor::CpuMonitor(QObject *parent)
    : QObject(parent),
      m_cpuWidget(nullptr)
{
}

void CpuMonitor::initialize()
{

}

void CpuMonitor::reset()
{

}

MonitorBaseWidget *CpuMonitor::moduleWidget()
{
    if (!m_cpuWidget) {
        m_cpuWidget = new CpuWidget;
    }

    return m_cpuWidget;
}

const QString CpuMonitor::name() const
{
    return QStringLiteral("cpu monitor");
}

CpuMonitor::~CpuMonitor()
{

}
