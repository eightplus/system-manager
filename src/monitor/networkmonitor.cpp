#include "networkmonitor.h"

NetworkMonitor::NetworkMonitor(QObject *parent)
    : QObject(parent),
      m_networkWidget(nullptr)
{
}

void NetworkMonitor::initialize()
{

}

void NetworkMonitor::reset()
{

}

MonitorBaseWidget *NetworkMonitor::moduleWidget()
{
    if (!m_networkWidget) {
        m_networkWidget = new NetworkWidget;
    }

    return m_networkWidget;
}

const QString NetworkMonitor::name() const
{
    return QStringLiteral("network monitor");
}

NetworkMonitor::~NetworkMonitor()
{

}
