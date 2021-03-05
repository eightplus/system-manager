#ifndef PROCESSMONITOR_H
#define PROCESSMONITOR_H

#include "monitorinterface.h"
#include "processwidget.h"

class ProcessMonitor : public QObject, public MonitorInterface
{
    Q_OBJECT

public:
    explicit ProcessMonitor(QObject *parent = 0);
    ~ProcessMonitor();

    void initialize();
    void reset();
    MonitorBaseWidget *moduleWidget();
    const QString name() const;

private:
    ProcessWidget *m_processWidget;
};

#endif // PROCESSMONITOR_H
