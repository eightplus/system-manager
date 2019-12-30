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

#include "infocard.h"
#include "infogroup.h"
#include "infoitems.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

InfoCard::InfoCard(const QString &name, QWidget *parent)
    : QFrame(parent)
    , m_titleLabel(nullptr)
    , m_infoItems(new InfoItems(this))
    , m_infoGroup(new InfoGroup)
    , m_name(name)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_infoItems->setAccessibleName(name);

    m_infoGroup->appendItem(m_infoItems);//扩展：支持向InfoGroup添加多个InfoItems，目前只添加一个即可

    QVBoxLayout *m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_infoGroup);
    m_mainLayout->setContentsMargins(30, 0, 0, 0);
    this->setLayout(m_mainLayout);
}

InfoCard::~InfoCard()
{
    if (m_titleLabel)
        m_titleLabel->deleteLater();

    QLayoutItem *child;
    while ((child = m_infoGroup->layout()->takeAt(0)) != 0) {
      QFrame *item =  qobject_cast<QFrame*>(child->widget());
      if (item)
          item->deleteLater();
      delete child;
    }

    delete m_infoGroup;
}

void InfoCard::setTitleVisible(const bool b)
{
    if (b) {
        if (!m_titleLabel)
            m_titleLabel = new QLabel;
        m_infoGroup->insertItem(0, m_titleLabel);
        m_titleLabel->setText(m_name);
    }
    else {
        if (m_titleLabel) {
            m_infoGroup->removeItem(m_titleLabel);
            m_titleLabel->deleteLater();
            m_titleLabel = nullptr;
        }
    }
}

void InfoCard::setInfo(const StringMap &result)
{
    if (m_infoItems) {
        m_infoItems->setInfo(result);
    }
}
