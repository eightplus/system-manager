#ifndef APTMANAGER_H
#define APTMANAGER_H

#include "plugininterface.h"

#include <QFrame>

class AptWidget;

class AptManager : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "com.eightplus.Plugin.PluginInterface" FILE "apt.json")
#endif

public:
    explicit AptManager(QObject* parent = 0);

    void initialize();
    const QString name() const;
    QWidget *centralWidget();

private:
    AptWidget *m_aptWidget;
};

#endif // APTMANAGER_H
