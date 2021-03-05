#include "autostartwidget.h"
#include "autostartview.h"
#include "autostartmodel.h"
#include "autostartdelegate.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

AutoStartWidget::AutoStartWidget(QWidget *parent)
    : QWidget(parent)
    , m_clearAllButton(new QPushButton)
    , m_autostartView(new AutoStartView)
    , m_autostartModel(new AutoStartModel)
    , m_autostartDelegate(new AutoStartDelegate)
    , m_tipLabel(new QLabel(tr("No autostart items")))
{
    this->setStyleSheet("QWidget{background-color: rgba(255, 255, 255, 10);}");
    this->setContentsMargins(0, 0, 0, 0);

    m_clearAllButton->setText(tr("Clear all autostart items"));
    m_clearAllButton->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 10); padding: 5px 0;}");
    m_clearAllButton->setContentsMargins(0, 0, 0, 0);

    m_autostartView->setEditTriggers(QListView::NoEditTriggers);
    m_autostartView->setModel(m_autostartModel);
    m_autostartView->setItemDelegate(m_autostartDelegate);

    m_tipLabel->setAlignment(Qt::AlignCenter);
    m_tipLabel->setVisible(false);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(2);
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_clearAllButton);
    layout->addWidget(m_autostartView);
    layout->addWidget(m_tipLabel);
    this->setLayout(layout);

    this->initConnections();
}

void AutoStartWidget::initConnections()
{
    connect(m_autostartDelegate, &AutoStartDelegate::removeBtnClicked, this, [=] () {
        const QModelIndex &index = m_autostartView->currentHoverIndex();
        m_autostartView->closePersistentEditor(index);
        m_autostartModel->showAnimationToRemoveSingleItem(index, m_autostartView->width());
    });
    connect(m_clearAllButton, &QPushButton::clicked, this, [=] () {
        m_autostartModel->showAnimationToClearAllItmes(m_autostartView->width());
    });
    connect(m_autostartModel, &AutoStartModel::removeAllAnimationFinished, m_autostartModel, &AutoStartModel::clearAllAutostartItems);
    connect(m_autostartModel, &AutoStartModel::removeSingleAnimationFinished, m_autostartModel, &AutoStartModel::removeSingleItem);
    connect(m_autostartModel, &AutoStartModel::removeSingleAnimationFinished, this, [=] (const QModelIndex &index) {
        if (m_autostartModel->rowCount(QModelIndex()) <= index.row()) {
            return;
        }

        m_autostartView->openPersistentEditor(m_autostartView->currentHoverIndex());
    });
    connect(m_autostartModel, &AutoStartModel::modelStateChanged, this, [=] (bool clear) {
        if (clear) {
            m_clearAllButton->setVisible(false);
            m_autostartView->setVisible(false);
            m_tipLabel->setVisible(true);
        }
        else {
            m_clearAllButton->setVisible(true);
            m_autostartView->setVisible(true);
            m_tipLabel->setVisible(false);
        }
    });
}
