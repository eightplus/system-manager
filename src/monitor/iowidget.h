#ifndef IOWIDGET_H
#define IOWIDGET_H

#include "monitorbasewidget.h"

#include <QPushButton>
#include <QVBoxLayout>

class IoWidget : public MonitorBaseWidget
{
    Q_OBJECT

public:
    explicit IoWidget();

private:
    QPushButton *m_btn;
};


#endif // IOWIDGET_H
