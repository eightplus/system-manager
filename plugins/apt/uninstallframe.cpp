#include "uninstallframe.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

UnInstallFrame::UnInstallFrame(QWidget *parent)
    :QFrame(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(10);

    initContent();
}

void UnInstallFrame::initContent()
{
    QLabel *title = new QLabel(tr("Content UnInstall"));
    m_layout->addSpacing(10);
    m_layout->addWidget(title);
}
