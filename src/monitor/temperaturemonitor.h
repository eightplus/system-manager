#ifndef TEMPERATUREMONITOR_H
#define TEMPERATUREMONITOR_H

#include "monitorinterface.h"
#include "temperaturewidget.h"

class TemperatureMonitor : public QObject, public MonitorInterface
{
    Q_OBJECT

public:
    explicit TemperatureMonitor(QObject *parent = 0);
    ~TemperatureMonitor();

    void initialize();
    void reset();
    MonitorBaseWidget *moduleWidget();
    const QString name() const;

private:
    TemperatureWidget *m_temperatureWidget;
};

#endif // TEMPERATUREMONITOR_H
