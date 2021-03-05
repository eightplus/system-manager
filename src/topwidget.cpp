#include "topwidget.h"
#include "toptoolbar.h"
#include "readmewidget.h"
#include "authorwidget.h"

#include <QApplication>
#include <QPainter>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include <QStyleOption>
#include <QPushButton>
#include <QShortcut>
#include <QAction>
#include <QMenu>

TopWidget::TopWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setObjectName("topWidget");
//    this->setAutoFillBackground(true);
//    QPalette palette(this->palette());
//    palette.setColor(QPalette::Background, QColor("#E4E7EA"));
//    this->setPalette(palette);

    this->initUI();
}

TopWidget::~TopWidget()
{
    QLayoutItem *child;
    while ((child = m_layout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
}

void TopWidget::initUI()
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);

    this->initReadmeWidget();
}

void TopWidget::displayDefaultPage()
{
    m_readmeWidget->setVisible(true);
    m_authorWidget->setVisible(false);
}

void TopWidget::initReadmeWidget()
{
    m_readmeWidget = new ReadmeWidget(this);
    connect(m_readmeWidget, &ReadmeWidget::requestShowBackBtn, this, [=] () {
        emit requestBack();
        m_readmeWidget->setVisible(false);
        m_authorWidget->setVisible(true);
    });
    m_layout->addWidget(m_readmeWidget);

    m_authorWidget = new AuthorWidget(this);
    m_layout->addWidget(m_authorWidget);
    m_readmeWidget->setVisible(true);
    m_authorWidget->setVisible(false);
}

void TopWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
