#include "deviceframe3.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

DeviceFrame3::DeviceFrame3(QWidget *parent)
    :QFrame(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(10);

    initContent();
}

void DeviceFrame3::initContent()
{
    QLabel *title = new QLabel(tr("Content Device 3"));
    m_layout->addSpacing(10);
    m_layout->addWidget(title);
}
