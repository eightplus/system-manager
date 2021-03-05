#include "autostartview.h"
#include "autostartmodel.h"

AutoStartView::AutoStartView(QWidget *parent) : QListView(parent)
{
    this->setMouseTracking(true);
    this->setFrameStyle(QFrame::NoFrame);
    this->setUpdatesEnabled(true);
    this->setStyleSheet("QListView {background-color: rgba(255, 255, 255, 10);}");
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollMode(QListView::ScrollPerPixel);
    this->setSpacing(0);
    this->setContentsMargins(0, 0, 0, 0);

    connect(this, &AutoStartView::entered, this, [=] (const QModelIndex &index) {
        m_currentIndex = index;
        static_cast<AutoStartModel *>(model())->setHoverIndex(m_currentIndex);

        if (m_previousIndex != m_currentIndex) {
            this->listViewCurrentHoverChanged(m_previousIndex, m_currentIndex);
            m_previousIndex = m_currentIndex;
        }
    });
}

const QModelIndex &AutoStartView::currentHoverIndex() const
{
    return m_currentIndex;
}

void AutoStartView::enterEvent(QEvent *event)
{
    if (m_currentIndex.isValid()) {
        openPersistentEditor(m_currentIndex);
    }

    QWidget::enterEvent(event);
}

void AutoStartView::leaveEvent(QEvent *event)
{
    if (m_currentIndex.isValid()) {
        closePersistentEditor(m_currentIndex);
        static_cast<AutoStartModel *>(model())->setHoverIndex(QModelIndex());
    }

    QWidget::leaveEvent(event);
}

void AutoStartView::listViewCurrentHoverChanged(const QModelIndex &previous, const QModelIndex &current)
{
    if (previous.isValid()) {
        closePersistentEditor(previous);
    }

    openPersistentEditor(current);
}
