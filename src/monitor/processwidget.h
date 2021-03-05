#ifndef PROCESSWIDGET_H
#define PROCESSWIDGET_H

#include "monitorbasewidget.h"

#include <QPushButton>
#include <QVBoxLayout>

class ProcessWidget : public MonitorBaseWidget
{
    Q_OBJECT

public:
    explicit ProcessWidget();

private:
    QPushButton *m_btn;
};


#endif // PROCESSWIDGET_H
