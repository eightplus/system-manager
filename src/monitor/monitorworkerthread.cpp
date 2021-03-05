#include "monitorworkerthread.h"

MonitorWorkerThread::MonitorWorkerThread(MonitorInterface *interface, QObject *parent)
    : QThread(parent),
      m_interface(interface)
{

}

void MonitorWorkerThread::run()
{
    m_interface->initialize();

    qApp->processEvents();

    emit moduleInitFinished(m_interface);
}
