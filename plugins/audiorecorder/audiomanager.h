#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "plugininterface.h"

#include <QFrame>

class AudioManager : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "com.eightplus.Plugin.PluginInterface" FILE "audiorecorder.json")
#endif

public:
    explicit AudioManager(QObject* parent = 0);

    void initialize();
    const QString name() const;
    QWidget *centralWidget();

private:
    QFrame *m_frame;
};

#endif // AUDIOMANAGER_H
