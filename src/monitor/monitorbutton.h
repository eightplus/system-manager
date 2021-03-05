#ifndef MONITOR_BTN_WIDGET_H
#define MONITOR_BTN_WIDGET_H

#include <QWidget>
#include <QLabel>

class MonitorButton : public QWidget
{
    Q_OBJECT

public:
    enum MonitorCatagary {
        Cpu = 0,
        Memory,
        Disk,
        Process,
        Network,
        IO,
        Temperature,
        Invalid,
    };
    Q_ENUM(MonitorCatagary)

    explicit MonitorButton(QWidget *parent = nullptr);
    ~MonitorButton();

    MonitorCatagary getCatagary()   {   return m_catagary;    }
    void setIconAndtext(MonitorCatagary catagary, const QString &icon, const QString &text);
    void updateQssProperty(const char *name, const QVariant &value);

signals:
    void clicked(MonitorCatagary catagary);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QLabel *m_iconLabel;
    QLabel *m_textLabel;
    MonitorCatagary m_catagary;
};

#endif // MONITOR_BTN_WIDGET_H
