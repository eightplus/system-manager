#include "toptoolbar.h"
#include "titlebuttongroup.h"

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
#include <QMouseEvent>

TopToolBar::TopToolBar(QWidget *parent) :
    QWidget(parent)
{
    this->setAutoFillBackground(true);
//    this->setObjectName("toptoolWidget");
//    this->setStyleSheet("QWidget#toptoolWidget{background:white; background-color: white;}");//E4E7EA

    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#eff4fa"));//"#0d87ca"
    this->setPalette(palette);

    this->initUI();
}

TopToolBar::~TopToolBar()
{
    if (m_titleStacked) {
        foreach (QObject *child, m_titleStacked->children()) {
            QWidget *w = static_cast<QWidget *>(child);
            w->deleteLater();
        }
        delete m_titleStacked;
    }

    QLayoutItem *child;
    while ((child = m_layout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
}

void TopToolBar::initUI()
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);

    this->initMenu();
    this->initTopTitleWidget();
}

void TopToolBar::setMiddleWidget(QWidget *w)
{
    QLayoutItem *child;
    while ((child = m_mLayout->takeAt(0)) != 0) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    if (w) {
        m_mLayout->addWidget(w);
    }
}

void TopToolBar::initLeftContent()
{
    QPixmap pixmap = QPixmap(":/res/tool.png");
    QLabel *logoLabel = new QLabel;
    logoLabel->setPixmap(pixmap);
    logoLabel->setFixedSize(pixmap.size());
    QLabel *textLabel = new QLabel;
    textLabel->setText(tr("系统管理器"));
    textLabel->adjustSize();

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(0,0,0,0);
    hLayout->addWidget(logoLabel, 0, Qt::AlignVCenter);
    hLayout->addWidget(textLabel, 0, Qt::AlignVCenter);

    QWidget *title = new QWidget;
    title->setAttribute(Qt::WA_TranslucentBackground);
    title->setLayout(hLayout);

    QPushButton *returnButton = new QPushButton();
    returnButton->setFixedSize(120, 36);
    returnButton->setIcon(QIcon(":/res/back.svg"));
    connect(returnButton, &QPushButton::clicked, this, [=] () {
        m_titleStacked->setCurrentIndex(0);
        emit requestShowHomePage();
    });

    m_titleStacked = new QStackedWidget;
    m_titleStacked->addWidget(title);
    m_titleStacked->addWidget(returnButton);
    m_titleStacked->setFixedHeight(returnButton->height());
    m_titleStacked->setCurrentIndex(0);

    m_layout->addWidget(m_titleStacked, 1, Qt::AlignLeft | Qt::AlignTop);
}

void TopToolBar::initMiddleContent()
{
    QWidget *w = new QWidget;
    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_mLayout = new QHBoxLayout(w);
    m_mLayout->setContentsMargins(0, 5, 0, 0);
    m_mLayout->setSpacing(0);

    m_layout->addWidget(w, 0, Qt::AlignTop);
}

void TopToolBar::initRightContent()
{
    /*TitleButtonGroup **/buttonGroup = new TitleButtonGroup;
    connect(buttonGroup, &TitleButtonGroup::showMenu, this, [=] () {
        if (parentWidget()->parentWidget()) {
            const QPoint gp = this->mapToGlobal(QPoint(0, 0));
            const QSize ms = m_menu->sizeHint();
            const QPoint p(gp.x() + width() - ms.width() - 30, gp.y() - 10);
            m_menu->popup(p);
        }
    });
    connect(buttonGroup, &TitleButtonGroup::showMax, this, [=] () {
        if (parentWidget()->window()->isMaximized()) {
            parentWidget()->window()->showNormal();
            buttonGroup->updateMaxIcon(false);
        }
        else {
            parentWidget()->window()->showMaximized();
            buttonGroup->updateMaxIcon(true);
        }
    });

    connect(this, &TopToolBar::requestUpdateMaxBtn, this, [=] {
        if (parentWidget()->window()->isMaximized()) {
            buttonGroup->updateMaxIcon(false);
        }
        else {
            buttonGroup->updateMaxIcon(true);
        }
    });
    connect(buttonGroup, &TitleButtonGroup::showMin, this, [=] () {
        if (parentWidget() && parentWidget()->parentWidget() && parentWidget()->parentWidget()->parentWidget()) {
            parentWidget()->parentWidget()->parentWidget()->showMinimized();
        }
    });
    connect(buttonGroup, &TitleButtonGroup::requestQuit, this, [=] () {
        qApp->quit();
    });

    m_layout->addWidget(buttonGroup, 1, Qt::AlignRight | Qt::AlignTop);
}

void TopToolBar::initTopTitleWidget()
{
    this->initLeftContent();
    this->initMiddleContent();
    this->initRightContent();
}

void TopToolBar::updateMaxButtonStatus(bool b)
{
    buttonGroup->updateMaxIcon(b);
}

void TopToolBar::setBackBtnVisible()
{
    m_titleStacked->setCurrentIndex(1);
}

void TopToolBar::initMenu()
{
    m_menu = new QMenu(this);
    QAction *settingAction = m_menu->addAction(tr("Settings"));
    m_menu->addSeparator();
    QAction *helpAction = m_menu->addAction(tr("Help"));
    QAction *aboutAction = m_menu->addAction(tr("About"));
    QAction *exitAction = m_menu->addAction(tr("Exit"));
    connect(settingAction, &QAction::triggered, this, &TopToolBar::onSetting);
    connect(helpAction, &QAction::triggered, this, &TopToolBar::onHelp);
    connect(aboutAction, &QAction::triggered, this, &TopToolBar::onAbout);
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);

    QShortcut *helpShortcut = new QShortcut(QKeySequence("F1"), this);
    QShortcut *exitShortcut = new QShortcut(QKeySequence("Ctrl+Q"), this);
    connect(helpShortcut, SIGNAL(activated()), this, SLOT(onHelp()));
    connect(exitShortcut, SIGNAL(activated()), qApp, SLOT(quit()));
}

void TopToolBar::onAbout()
{

    QWidget *w = window();
    QPoint gp = w->mapToGlobal(QPoint(0, 0));
    //dialog->move((w->width() - ad->width()) / 2 + gp.x(), (w->height() - ad->sizeHint().height()) / 2 + gp.y());*/
}

void TopToolBar::onHelp()
{

}

void TopToolBar::onSetting()
{

}

void TopToolBar::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        if (window()->isMaximized()) {
            this->updateMaxButtonStatus(false);
            window()->showNormal();
        }
        else if (!window()->isFullScreen()) {
            this->updateMaxButtonStatus(true);
            window()->showMaximized();
        }
    }

    QWidget::mouseDoubleClickEvent(e);
}
