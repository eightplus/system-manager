#ifndef DISKWIDGET_H
#define DISKWIDGET_H

#include "monitorbasewidget.h"

#include <QPushButton>
#include <QVBoxLayout>

class DiskWidget : public MonitorBaseWidget
{
    Q_OBJECT

public:
    explicit DiskWidget();

private:
    QPushButton *m_btn;
};


#endif // DISKWIDGET_H
