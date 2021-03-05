#include "deviceframe2.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

DeviceFrame2::DeviceFrame2(QWidget *parent)
    :QFrame(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(10);

    initContent();
}

void DeviceFrame2::initContent()
{
    QLabel *title = new QLabel(tr("Content Device 2"));
    m_layout->addSpacing(10);
    m_layout->addWidget(title);
}
