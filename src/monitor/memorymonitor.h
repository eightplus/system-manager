#ifndef MEMORYMONITOR_H
#define MEMORYMONITOR_H

#include "monitorinterface.h"
#include "memorywidget.h"

class MemoryMonitor : public QObject, public MonitorInterface
{
    Q_OBJECT

public:
    explicit MemoryMonitor(QObject *parent = 0);
    ~MemoryMonitor();

    void initialize();
    void reset();
    MonitorBaseWidget *moduleWidget();
    const QString name() const;

private:
    MemoryWidget *m_memoryWidget;
};

#endif // MEMORYMONITOR_H
