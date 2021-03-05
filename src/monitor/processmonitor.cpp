#include "processmonitor.h"

ProcessMonitor::ProcessMonitor(QObject *parent)
    : QObject(parent),
      m_processWidget(nullptr)
{
}

void ProcessMonitor::initialize()
{

}

void ProcessMonitor::reset()
{

}

MonitorBaseWidget *ProcessMonitor::moduleWidget()
{
    if (!m_processWidget) {
        m_processWidget = new ProcessWidget;
    }

    return m_processWidget;
}

const QString ProcessMonitor::name() const
{
    return QStringLiteral("process monitor");
}

ProcessMonitor::~ProcessMonitor()
{

}
