#include "aptmanager.h"
#include "aptwidget.h"

AptManager::AptManager(QObject *parent)
    : QObject(parent)
{

}

void AptManager::initialize()
{
    m_aptWidget = new AptWidget;
}

QWidget *AptManager::centralWidget()
{
    return m_aptWidget;
}

const QString AptManager::name() const
{
    return QStringLiteral("apt");
}
