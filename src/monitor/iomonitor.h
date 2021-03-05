#ifndef IOMONITOR_H
#define IOMONITOR_H

#include "monitorinterface.h"
#include "iowidget.h"

class IoMonitor : public QObject, public MonitorInterface
{
    Q_OBJECT

public:
    explicit IoMonitor(QObject *parent = 0);
    ~IoMonitor();

    void initialize();
    void reset();
    MonitorBaseWidget *moduleWidget();
    const QString name() const;

private:
    IoWidget *m_ioWidget;
};

#endif // IOMONITOR_H
