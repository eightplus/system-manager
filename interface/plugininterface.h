#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtCore>

class PluginInterface
{
public:
    //virtual ~PluginInterface(){}
    virtual void initialize() = 0;
    virtual const QString name() const = 0;
    virtual QWidget *centralWidget() = 0;//返回模块主Widget；
};

QT_BEGIN_NAMESPACE
#define PluginInterface_iid "com.eightplus.Plugin.PluginInterface"

//Q_DECLARE_INTERFACE定义在在qobject.h中，用来告诉Qt meta-object system 这个接口名称
Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)

QT_END_NAMESPACE

#endif // PLUGININTERFACE_H
