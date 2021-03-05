#ifndef CPUWIDGET_H
#define CPUWIDGET_H

#include "monitorbasewidget.h"

#include <QPushButton>
#include <QVBoxLayout>

class CpuWidget : public MonitorBaseWidget
{
    Q_OBJECT

public:
    explicit CpuWidget();

private:
    QPushButton *m_btn;
};


#endif // CPUWIDGET_H
