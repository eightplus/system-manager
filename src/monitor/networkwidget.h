#ifndef NETWORKWIDGET_H
#define NETWORKWIDGET_H

#include "monitorbasewidget.h"

#include <QPushButton>
#include <QVBoxLayout>

class NetworkWidget : public MonitorBaseWidget
{
    Q_OBJECT

public:
    explicit NetworkWidget();

private:
    QPushButton *m_btn;
};


#endif // NETWORKWIDGET_H
