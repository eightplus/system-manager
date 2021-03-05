#include "videowidget.h"

#include <QVBoxLayout>
#include <QPushButton>

VideoWidget::VideoWidget(QWidget *parent)
    : QWidget(parent)
{
    m_okBtn = new QPushButton(this);
    m_okBtn->setText("video btn");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_okBtn, 0, Qt::AlignCenter);
    this->setLayout(layout);
}
