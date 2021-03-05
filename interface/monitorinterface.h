#ifndef MONITORINTERFACE_H
#define MONITORINTERFACE_H

#include <QtCore>

class MonitorBaseWidget;

class MonitorInterface
{
public:
    MonitorInterface() {}
    virtual ~MonitorInterface() {}

    virtual void initialize() = 0;
    virtual void reset() = 0;
    virtual const QString name() const = 0 ;

    // 返回模块主Widget；
    virtual MonitorBaseWidget *moduleWidget() = 0;
};

#endif // MONITORINTERFACE_H
