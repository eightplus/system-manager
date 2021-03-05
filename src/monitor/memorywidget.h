#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include "monitorbasewidget.h"

#include <QPushButton>
#include <QVBoxLayout>

class MemoryWidget : public MonitorBaseWidget
{
    Q_OBJECT

public:
    explicit MemoryWidget();

private:
    QPushButton *m_btn;
};


#endif // MEMORYWIDGET_H
