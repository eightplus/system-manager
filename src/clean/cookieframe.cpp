#include "cookieframe.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

CookieFrame::CookieFrame(QWidget *parent)
    :QFrame(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(10);

    initContent();
}

void CookieFrame::initContent()
{
    QLabel *title = new QLabel(tr("Content cookie"));
    m_layout->addSpacing(10);
    m_layout->addWidget(title);
}
