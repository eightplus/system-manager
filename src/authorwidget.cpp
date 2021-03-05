#include "authorwidget.h"

#include <QFrame>
#include <QResizeEvent>
#include <QHBoxLayout>
#include <QLabel>

AuthorWidget::AuthorWidget(QWidget *parent)
    : QFrame(parent)
    , m_label(new QLabel(this))
{
    m_label->setText("Author: lixiang");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_label);
}

void AuthorWidget::resizeEvent(QResizeEvent *e)
{
    QFrame::resizeEvent(e);
}
