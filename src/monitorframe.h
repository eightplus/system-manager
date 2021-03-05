#ifndef MONITORFRAME_H
#define MONITORFRAME_H

#include <QFrame>
#include <QMap>
#include "monitor/monitorbutton.h"

class MonitorButton;
class QHBoxLayout;
class QVBoxLayout;
class QStackedWidget;
class MonitorInterface;

class MonitorFrame : public QFrame
{
    Q_OBJECT
public:
    explicit MonitorFrame(QWidget *parent = 0);
    ~MonitorFrame();

    void initUI();
    void initLeftContent();
    void initRightContent();
    void refreshNavBar(const QStringList &types);
    void refreshWidgets(const QStringList &types);

public slots:
    void onMonitorButtonClicked(MonitorButton::MonitorCatagary catagary);
    void updateDatas();

    void loadModule(MonitorInterface * const module);
    void onModuleInitFinished(MonitorInterface * const inter);
    void addNavigationItem(const QString &name, bool first);

private:
    QHBoxLayout *m_layout;
    QVBoxLayout *m_lLayout;
    QVBoxLayout *m_rLayout;
    QList<MonitorButton*> m_modules_list;
    QMap<MonitorButton::MonitorCatagary, QWidget*> m_modules_map;
    QStackedWidget *m_stackWidget;
    MonitorButton::MonitorCatagary m_currentCatagary;

    int m_moduleLoadDelay;
    QList<MonitorInterface *> m_moduleInterfaces;
    QMap<MonitorInterface *, bool> m_moduleActivable;
};

#endif // MONITORFRAME_H
