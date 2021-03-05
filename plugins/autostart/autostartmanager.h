#ifndef AUTOSTARTMANAGER_H
#define AUTOSTARTMANAGER_H

#include "plugininterface.h"

#include <QFrame>
class AutoStartWidget;

class AutostartManager : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "com.eightplus.Plugin.PluginInterface" FILE "autostart.json")
#endif

public:
    explicit AutostartManager(QObject* parent = 0);

    void initialize();
    const QString name() const;
    QWidget *centralWidget();

private:
    AutoStartWidget *m_autostartWidget = nullptr;
};

#endif // AUTOSTARTMANAGER_H
