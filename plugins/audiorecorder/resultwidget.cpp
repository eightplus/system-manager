#include "resultwidget.h"

#include <QVBoxLayout>
#include <QLabel>

ResultWidget::ResultWidget(QWidget *parent)
    : QWidget(parent)
      , m_label(new QLabel)
{
    m_label->setStyleSheet("QLabel{color: rgba(255, 255, 255, 0.4);}");
    m_label->setText("audio recoder finish page");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_label, 0, Qt::AlignCenter);
    layout->addStretch();
    this->setLayout(layout);
}

void ResultWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);

    emit cancelled();
}
