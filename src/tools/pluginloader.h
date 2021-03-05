#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QObject>

class PluginLoader : public QObject
{
    Q_OBJECT

public:
    explicit PluginLoader(QObject *parent = 0);

signals:
    void pluginAdded(QWidget * const w, const QString &name);

public slots:
    void loadPlugins();
};

#endif // PLUGINLOADER_H
