#include "aptwidget.h"
#include "selectfileframe.h"
#include "installframe.h"
#include "uninstallframe.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedLayout>

#define NAVIGATION_WIDTH 150
#define NAVIGATION_HEIGHT 36

AptWidget::AptWidget(QWidget *parent)
    : QWidget(parent)
    , m_stackedLayout(new QStackedLayout)
    , m_navButtonsGroup(new QButtonGroup)
    , m_layout(new QHBoxLayout(this))
    , m_pageType(Invalid)
{
    m_stackedLayout->setMargin(0);
    m_stackedLayout->setSpacing(0);
    m_navButtonsGroup->setExclusive(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->initUI();
}

AptWidget::~AptWidget()
{
    QLayoutItem *child;
    while ((child = m_lLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

    while ((child = m_rLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

    while ((child = m_layout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

//    qDeleteAll(m_navButtonsGroup->children());
    for (QAbstractButton* button : m_navButtonsGroup->buttons()) {
        m_navButtonsGroup->removeButton(button);
    }
}


void AptWidget::initUI()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);

    this->initLeftContent();
    this->initRightContent();

    m_navButtonsGroup->buttons().first()->click();

//    for (QAbstractButton* button : m_navButtonsGroup->buttons()) {
//        QPushButton* btn = qobject_cast<QPushButton*>(button);
//        if (btn == nullptr) {
//        }
//    }
}

void AptWidget::initLeftContent()
{
    QWidget *leftWidget = new QWidget;
    leftWidget->setFixedWidth(150);
    leftWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    leftWidget->setObjectName("LeftNavWidget");
    leftWidget->setStyleSheet("#LeftNavWidget {border:solid #888888;border-right-width: 1px;}"
                              "#LeftNavWidget > QPushButton {margin: 0;text-align: left;padding: 0px 15px;border: none;}"
                              "#LeftNavWidget > QPushButton:checked {color: #ffffff;font-weight: 500;background-color: rgba(10,10,10,50);border: 1px solid rgba(255, 255, 255, .1);border-left: none;border-right: none;}");
    m_lLayout = new QVBoxLayout(leftWidget);
    m_lLayout->setContentsMargins(0, 0, 0, 0);
    m_lLayout->setSpacing(0);
    m_layout->addWidget(leftWidget, 0, Qt::AlignLeft);

    QPushButton *selectFileBtn = new QPushButton();
    selectFileBtn->setText(tr("select"));
    selectFileBtn->setFixedSize(NAVIGATION_WIDTH, NAVIGATION_HEIGHT);
    m_lLayout->addWidget(selectFileBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);
    m_navButtonsGroup->addButton(selectFileBtn);
    connect(selectFileBtn, &QPushButton::clicked, this, [=] { onNavButtonClicked(SelectFilePage); });

    QPushButton *installBtn = new QPushButton();
    installBtn->setText(tr("install"));
    installBtn->setFixedSize(NAVIGATION_WIDTH, NAVIGATION_HEIGHT);
    m_lLayout->addWidget(installBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);
    m_navButtonsGroup->addButton(installBtn);
    connect(installBtn, &QPushButton::clicked, this, [=] { onNavButtonClicked(InstallPage); });

    QPushButton *uninstallBtn = new QPushButton();
    uninstallBtn->setText(tr("uninstall"));
    uninstallBtn->setFixedSize(NAVIGATION_WIDTH, NAVIGATION_HEIGHT);
    m_lLayout->addWidget(uninstallBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);
    m_navButtonsGroup->addButton(uninstallBtn);
    connect(uninstallBtn, &QPushButton::clicked, this, [=] { onNavButtonClicked(UnInstallPage); });

    m_navButtonsGroup->setExclusive(true);
    m_lLayout->addStretch();
}

void AptWidget::setNavgationEnabled(const bool enabled)
{
    for (auto *button : m_navButtonsGroup->buttons()) {
        button->setEnabled(enabled);
    }
}

 void AptWidget::onNavButtonClicked(PageType index)
 {
    if (index == m_pageType) return;

    switch (index)
    {
    case SelectFilePage:
        this->showSelectFilePage();
        break;
    case InstallPage:
        this->showInstallPage();
        break;
    case UnInstallPage:
        this->showUninstallPage();
        break;
    default: break;
    }

}

void AptWidget::showSelectFilePage()
{
    m_pageType = SelectFilePage;

    QWidget *m_currentWidget = m_stackedLayout->currentWidget();
    if (m_currentWidget != 0) {
        m_currentWidget->deleteLater();
        m_currentWidget = nullptr;
    }

    m_selectFileFrame = new SelectFileFrame();
    m_stackedLayout->addWidget(m_selectFileFrame);
}

void AptWidget::showInstallPage()
{
    m_pageType = InstallPage;

    QWidget *m_currentWidget = m_stackedLayout->currentWidget();
    if (m_currentWidget != 0) {
        m_currentWidget->deleteLater();
    }

    m_installFrame = new InstallFrame();
    m_stackedLayout->addWidget(m_installFrame);
}

void AptWidget::showUninstallPage()
{
    m_pageType = UnInstallPage;

    QWidget *m_currentWidget = m_stackedLayout->currentWidget();
    if (m_currentWidget != 0) {
        m_currentWidget->deleteLater();
    }

    m_uninstallFrame = new UnInstallFrame();
    m_stackedLayout->addWidget(m_uninstallFrame);
}

void AptWidget::initRightContent()
{
    m_stackedLayout->setContentsMargins(0, 0, 0, 0);
    m_stackedLayout->setSpacing(0);

    // clear old widgets
    QLayoutItem *child;
    while ((child = m_stackedLayout->takeAt(0)) != 0) {
        QWidget *w = child->widget();
        if (w) {
            w->setParent(NULL);
            m_stackedLayout->removeWidget(w);
            w->deleteLater();
        }
        delete child;
    }

    QWidget *rightWidget = new QWidget;
    rightWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_rLayout = new QVBoxLayout(rightWidget);//rightWidget->setLayout(m_rLayout);
    m_rLayout->setContentsMargins(0, 0, 6, 0);
    m_rLayout->setSpacing(0);
    m_layout->addWidget(rightWidget);//m_layout->addWidget(rightWidget, 1, Qt::AlignLeft);//将导致m_stackWidget下所有界面缩放根据窗口大小自动缩放
    m_rLayout->addLayout(m_stackedLayout);
}
