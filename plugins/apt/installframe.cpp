#include "installframe.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

InstallFrame::InstallFrame(QWidget *parent)
    :QFrame(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(10);

    initContent();
}

void InstallFrame::initContent()
{
    QLabel *title = new QLabel(tr("Content Install"));
    m_layout->addSpacing(10);
    m_layout->addWidget(title);
}
