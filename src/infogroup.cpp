/*
 * Copyright (C) 2019 ~ 2020 kobe24_lixiang@126.com
 *
 * Authors:
 *  lixiang    kobe24_lixiang@126.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "infogroup.h"

#include <QVBoxLayout>
#include <QEvent>
#include <QTimer>

InfoGroup::InfoGroup(QFrame *parent) :
    QFrame(parent),
    m_layout(new QVBoxLayout),
    m_timer(new QTimer(this))
{
    m_layout->setMargin(0);
    m_layout->setSpacing(1);
    this->setLayout(m_layout);

    m_timer->setSingleShot(true);
    m_timer->setInterval(15);
    connect(m_timer, &QTimer::timeout, this, &InfoGroup::updateHeight, Qt::QueuedConnection);
}

InfoGroup::~InfoGroup()
{
    for (int i = 0; i != itemCount(); ++i) {
        QLayoutItem *item = m_layout->takeAt(0);
        QWidget *w = item->widget();
        w->removeEventFilter(this);
        w->setParent(nullptr);
        delete item;
    }
}

void InfoGroup::insertItem(const int index, QFrame *item)
{
    m_layout->insertWidget(index, item);
    item->installEventFilter(this);
    m_timer->start();
}

void InfoGroup::appendItem(QFrame *item)
{
    insertItem(m_layout->count(), item);
}

void InfoGroup::removeItem(QFrame *item)
{
    m_layout->removeWidget(item);
    item->removeEventFilter(this);
    m_timer->start();
}

void InfoGroup::setSpacing(const int spaceing)
{
    m_layout->setSpacing(spaceing);
    m_timer->start();
}

int InfoGroup::itemCount() const
{
    return m_layout->count();
}

void InfoGroup::updateHeight()
{
    Q_ASSERT(sender() == m_timer);

    setFixedHeight(m_layout->sizeHint().height());
}

bool InfoGroup::eventFilter(QObject *, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::Resize:
        m_timer->start();
        break;
    default:;
    }

    return false;
}
