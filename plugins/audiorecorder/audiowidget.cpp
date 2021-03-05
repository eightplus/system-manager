#include "audiowidget.h"

#include <QVBoxLayout>
#include <QPushButton>

AudioWidget::AudioWidget(QWidget *parent)
    : QWidget(parent)
{
    m_okBtn = new QPushButton(this);
    m_okBtn->setText("OK");
    connect(m_okBtn, &QPushButton::clicked, this, &AudioWidget::requestFinish);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_okBtn, 0, Qt::AlignCenter);
    this->setLayout(layout);
}
