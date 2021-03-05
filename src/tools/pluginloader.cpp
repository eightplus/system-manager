#include "pluginloader.h"
#include "plugininterface.h"

#include <QDebug>
#include <QDir>
#include <QLibrary>
#include <QPluginLoader>
#include <QWidget>

PluginLoader::PluginLoader(QObject *parent)
    : QObject(parent)
{
}

void PluginLoader::loadPlugins()
{
    bool hasPlugins = false;
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.setSorting(QDir::Name);

#ifdef QT_DEBUG
    pluginsDir.cd("../plugins");
#else
    pluginsDir.cd("../plugins");
//    pluginsDir.cd("../lib/momo-system-manager/plugins");
#endif

    QStringList plugins = pluginsDir.entryList(QDir::Files);
    // pluginsDir.setSorting not working as expected on loongson.
    qSort(plugins.begin(), plugins.end());

    for (const QString file : plugins) {
        if (!QLibrary::isLibrary(file))
            continue;

        // load library
        QPluginLoader *pluginLoader = new QPluginLoader(pluginsDir.absoluteFilePath(file), this);
        qDebug() << "load plugin: " << pluginLoader->metaData();

        PluginInterface *interface = qobject_cast<PluginInterface *>(pluginLoader->instance());
        if (!interface)
        {
            qWarning() << pluginLoader->errorString();
            pluginLoader->unload();
            pluginLoader->deleteLater();
            return;
        } else {
            qDebug() << "get plugin interface: " << interface;
        }

        interface->initialize();
        QWidget *w = interface->centralWidget();
        emit pluginAdded(w, interface->name());
        hasPlugins = true;
    }

    if (hasPlugins) {
        emit pluginAdded(nullptr, "over");
    }
}
