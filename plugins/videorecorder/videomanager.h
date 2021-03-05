#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include "plugininterface.h"

#include <QFrame>

class VideoWidget;

class VideoManager : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "com.eightplus.Plugin.PluginInterface" FILE "videorecorder.json")
#endif

public:
    explicit VideoManager(QObject* parent = 0);

    void initialize();
    const QString name() const;
    QWidget *centralWidget();

private:
    VideoWidget *m_videoWidget;
};

#endif // VIDEOMANAGER_H
