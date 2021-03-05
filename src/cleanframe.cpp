#include "cleanframe.h"
#include "clean/cleanertoolbar.h"
#include "clean/cacheframe.h"
#include "clean/cookieframe.h"
#include "clean/historyframe.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QStackedWidget>

CleanFrame::CleanFrame(QWidget *parent) :
    QFrame(parent)
  , m_stackWidget(new QStackedWidget(this))
  , m_layout(new QVBoxLayout(this))
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->initUI();
}

CleanFrame::~CleanFrame()
{
    if (m_stackWidget) {
        foreach (QObject *child, m_stackWidget->children()) {
            QWidget *w = static_cast<QWidget *>(child);
            w->deleteLater();
        }
        delete m_stackWidget;
    }

    QLayoutItem *child;
    while ((child = m_layout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
}

void CleanFrame::initUI()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    m_stackWidget->setPalette(palette);
    m_stackWidget->setAutoFillBackground(true);
    m_stackWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    title_widget = new CleanerToolBar(this);
    connect(title_widget, SIGNAL(requestTurnPage(int)), this, SLOT(onTurnPage(int)));
//    title_widget->setFixedHeight(110);
//    title_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_layout->addWidget(title_widget, 0, Qt::AlignTop);

    m_cacheFrame = new CacheFrame(this);
    m_cookieFrame = new CookieFrame(this);
    m_historyFrame = new HistoryFrame(this);
    m_stackWidget->addWidget(m_cacheFrame);
    m_stackWidget->addWidget(m_cookieFrame);
    m_stackWidget->addWidget(m_historyFrame);
    connect(m_stackWidget, &QStackedWidget::currentChanged, this, [=] (int i) {
//        if (m_stackWidget->m_currentWidget() == m_cacheFrame) {

//        }
    });

    QWidget *bottomWidget = new QWidget;
    bottomWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout *m_rLayout = new QVBoxLayout(bottomWidget);
    m_rLayout->setContentsMargins(0, 0, 6, 0);
    m_rLayout->setSpacing(0);
    m_rLayout->addWidget(m_stackWidget);
    m_layout->addWidget(bottomWidget);

    title_widget->turnPage("0");
    m_stackWidget->setCurrentIndex(0);
}

void CleanFrame::onTurnPage(int index)
{
    if (index == 0) {
        m_stackWidget->setCurrentWidget(m_cacheFrame);
    }
    else if (index == 1) {
        m_stackWidget->setCurrentWidget(m_cookieFrame);
    }
    else if (index == 2) {
        m_stackWidget->setCurrentWidget(m_historyFrame);
    }
}
