#include "homepage.h"
#include "topwidget.h"
#include "bottomwidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

HomeWidget::HomeWidget(QWidget *parent) : QFrame(parent)
    , m_layout(new QVBoxLayout(this))
{
//    if (parent) {
//        this->resize(parent->size());
//    }

    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);

    m_topWidget = new TopWidget(this);
    m_topWidget->setFixedHeight(240);
    connect(m_topWidget, &TopWidget::requestBack, this, &HomeWidget::requestBack);

    m_bottomToolbar = new BottomWidget(this);

    connect(m_bottomToolbar, &BottomWidget::infoBtnClicked, this, [=] () {
        emit requestSubWidget(0, tr("Information"));
    });
    connect(m_bottomToolbar, &BottomWidget::monitorBtnClicked, this, [=] () {
        emit requestSubWidget(1, tr("Monitor"));
    });
    connect(m_bottomToolbar, &BottomWidget::cleanBtnClicked, this, [=] () {
        emit requestSubWidget(2, tr("Cleaner"));
    });
    connect(m_bottomToolbar, &BottomWidget::toolsBtnClicked, this, [=] () {
        emit requestSubWidget(3, tr("Tools"));
    });

    m_layout->addWidget(m_topWidget);
    m_layout->addWidget(m_bottomToolbar);
}

HomeWidget::~HomeWidget()
{
    QLayoutItem *child;
    while ((child = m_layout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

//    while (m_layout->count() > 0) {
//        QWidget* w = m_layout->itemAt(0)->widget();
//        m_layout->removeWidget(w);
//        delete w;
//    }
}

void HomeWidget::showHomePage()
{
    m_topWidget->displayDefaultPage();
}
