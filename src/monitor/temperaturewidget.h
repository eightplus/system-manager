#ifndef TEMPERATUREWIDGET_H
#define TEMPERATUREWIDGET_H

#include "monitorbasewidget.h"

#include <QPushButton>
#include <QVBoxLayout>

class TemperatureWidget : public MonitorBaseWidget
{
    Q_OBJECT

public:
    explicit TemperatureWidget();

private:
    QPushButton *m_btn;
};


#endif // TEMPERATUREWIDGET_H
