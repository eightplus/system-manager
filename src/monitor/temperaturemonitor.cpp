#include "temperaturemonitor.h"

TemperatureMonitor::TemperatureMonitor(QObject *parent)
    : QObject(parent),
      m_temperatureWidget(nullptr)
{
}

void TemperatureMonitor::initialize()
{

}

void TemperatureMonitor::reset()
{

}

MonitorBaseWidget *TemperatureMonitor::moduleWidget()
{
    if (!m_temperatureWidget) {
        m_temperatureWidget = new TemperatureWidget;
    }

    return m_temperatureWidget;
}

const QString TemperatureMonitor::name() const
{
    return QStringLiteral("temperature monitor");
}

TemperatureMonitor::~TemperatureMonitor()
{

}
