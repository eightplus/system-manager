#ifndef NETWORKMONITOR_H
#define NETWORKMONITOR_H

#include "monitorinterface.h"
#include "networkwidget.h"

class NetworkMonitor : public QObject, public MonitorInterface
{
    Q_OBJECT

public:
    explicit NetworkMonitor(QObject *parent = 0);
    ~NetworkMonitor();

    void initialize();
    void reset();
    MonitorBaseWidget *moduleWidget();
    const QString name() const;

private:
    NetworkWidget *m_networkWidget;
};

#endif // NETWORKMONITOR_H
