#include "infoscrollpanel.h"

#include <QCursor>
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QScrollBar>
#include <QDebug>

InfoScrollPanel::InfoScrollPanel(QWidget *parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    m_label = new QLabel;
    QWidget *titleFrame = new QWidget;
    titleFrame->setObjectName("whiteWidget");
    titleFrame->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hlayout = new QHBoxLayout(titleFrame);
    hlayout->setContentsMargins(0, 3, 3, 0);
    hlayout->setSpacing(0);
    hlayout->addWidget(m_label);
    hlayout->addStretch();
    m_layout->addWidget(titleFrame);

    initScrollArea();
}

InfoScrollPanel::~InfoScrollPanel()
{
    //qDebug() << "InfoScrollPanel destroy!!!";
    QLayoutItem *child;
    while ((child = areaLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

    //No.2: delete m_stackWidget
    if (m_stackWidget) {
        foreach (QObject *child, m_stackWidget->children()) {
            QWidget *w = static_cast<QWidget *>(child);
            w->deleteLater();
        }
        delete m_stackWidget;
    }

    //No.3: delete m_layout
    while ((child = m_layout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
}

void InfoScrollPanel::initScrollArea()
{
    // Empty frame
    QLabel *errPage = new QLabel(tr("Error Page"));
    errPage->setAlignment(Qt::AlignCenter);
    errPage->setObjectName("ErroFrame");

    m_area = new QScrollArea;
    m_area->setWidgetResizable(true);
    m_area->setContentsMargins(0, 0, 0, 0);
    m_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //m_area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //m_area->setFrameStyle(QFrame::NoFrame);

    QScrollBar *sb = new QScrollBar();
    m_area->setVerticalScrollBar(sb);
    sb->setContextMenuPolicy(Qt::PreventContextMenu);

    QWidget *areaContent = new QWidget;
    areaContent->setObjectName("whiteWidget");
    areaLayout = new QVBoxLayout(areaContent);
    areaLayout->setContentsMargins(0, 0, 0, 0);
    areaLayout->setSpacing(0);

    m_area->setWidget(areaContent);

    m_stackWidget = new QStackedWidget;
    m_stackWidget->setContentsMargins(0, 0, 0, 0);
    m_stackWidget->addWidget(errPage);
    m_stackWidget->addWidget(m_area);
    m_stackWidget->setCurrentIndex(1);

    m_layout->addWidget(m_stackWidget);
}

void InfoScrollPanel::setTitle(const QString &title)
{
    m_label->setText(title);
}

void InfoScrollPanel::addContentWidget(QWidget *w)
{
    if (w) {
        areaLayout->addWidget(w);
    }
}
