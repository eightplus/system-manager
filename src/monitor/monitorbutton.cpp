#include "monitorbutton.h"

#include <QMouseEvent>
#include <QStyle>
#include <QVariant>
#include <QHBoxLayout>

MonitorButton::MonitorButton(QWidget *parent) :
    QWidget(parent)
    , m_iconLabel(new QLabel(this))
    , m_textLabel(new QLabel(this))
{
    this->setObjectName("monitorBtnwidget");
    this->setAttribute(Qt::WA_StyledBackground);
    this->setFixedSize(150, 40);

    m_iconLabel->setFixedSize(24, 24);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(5);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(m_iconLabel);
    layout->addWidget(m_textLabel);
    this->setLayout(layout);
}

MonitorButton::~MonitorButton()
{

}

void MonitorButton::setIconAndtext(MonitorCatagary catagary, const QString &icon, const QString &text)
{
    m_catagary = catagary;
    QPixmap pixmap(icon);
    pixmap = pixmap.scaled(m_iconLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    m_iconLabel->setPixmap(pixmap);
    m_textLabel->setText(text);
}

void MonitorButton::updateQssProperty(const char *name, const QVariant &value)
{
    this->setProperty(name, value);
    style()->unpolish(this);
    style()->polish(this);
    this->update();
}

void MonitorButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked(m_catagary);
    }
}
