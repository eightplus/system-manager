#ifndef MONITORWORKERTHREAD_H
#define MONITORWORKERTHREAD_H

#include "monitorinterface.h"

#include <QThread>

class MonitorWorkerThread : public QThread
{
    Q_OBJECT

public:
    explicit MonitorWorkerThread(MonitorInterface *interface, QObject *parent = 0);

signals:
    void moduleInitFinished(MonitorInterface *interface) const;

protected:
    void run();

private:
    MonitorInterface *m_interface;
};

#endif // MONITORWORKERTHREAD_H
