#include "autostartmanager.h"
#include "autostartwidget.h"

AutostartManager::AutostartManager(QObject *parent)
    : QObject(parent),
      m_autostartWidget(new AutoStartWidget)
{

}

void AutostartManager::initialize()
{

}

QWidget *AutostartManager::centralWidget()
{
    return m_autostartWidget;
}

const QString AutostartManager::name() const
{
    return QStringLiteral("autostart");
}
