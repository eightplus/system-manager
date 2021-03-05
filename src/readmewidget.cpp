#include "readmewidget.h"

#include <QFrame>
#include <QResizeEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

ReadmeWidget::ReadmeWidget(QWidget *parent)
    : QFrame(parent)
    , m_label(new QLabel(this))
    , m_btn(new QPushButton(this))
{
    m_label->setText("ReadMe page");
    m_btn->setFixedSize(130, 36);
    m_btn->setText(tr("View Author"));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_label);
    layout->addStretch();
    layout->addWidget(m_btn);

    connect(m_btn, &QPushButton::clicked, this, [=] () {
        emit requestShowBackBtn();
    });
}

void ReadmeWidget::resizeEvent(QResizeEvent *e)
{
    QFrame::resizeEvent(e);
}
