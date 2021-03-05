#ifndef DISKMONITOR_H
#define DISKMONITOR_H

#include "monitorinterface.h"
#include "diskwidget.h"

class DiskMonitor : public QObject, public MonitorInterface
{
    Q_OBJECT

public:
    explicit DiskMonitor(QObject *parent = 0);
    ~DiskMonitor();

    void initialize();
    void reset();
    MonitorBaseWidget *moduleWidget();
    const QString name() const;

private:
    DiskWidget *m_diskWidget;
};

#endif // DISKMONITOR_H
