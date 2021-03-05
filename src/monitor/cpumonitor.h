#ifndef CPUMONITOR_H
#define CPUMONITOR_H

#include "monitorinterface.h"
#include "cpuwidget.h"

class CpuMonitor : public QObject, public MonitorInterface
{
    Q_OBJECT

public:
    explicit CpuMonitor(QObject *parent = 0);
    ~CpuMonitor();

    void initialize();
    void reset();
    MonitorBaseWidget *moduleWidget();
    const QString name() const;

private:
    CpuWidget *m_cpuWidget;
};

#endif // CPUMONITOR_H
