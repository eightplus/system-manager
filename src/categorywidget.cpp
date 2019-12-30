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

#include "categorywidget.h"
#include "infocard.h"
#include "infogroup.h"

#include <QDebug>

CategoryWidget::CategoryWidget(const QString &name)
    : BaseWidget()
    , m_infoGroup(new InfoGroup)
    , m_vlayout(new QVBoxLayout)
{
    this->setObjectName(name);
    this->setTitle(name);

    //QVBoxLayout *mainLayout = static_cast<QVBoxLayout *>(layout());//m_baseMainLayout
    m_baseMainLayout->addWidget(m_infoGroup);
    m_baseMainLayout->addStretch(0);

    m_vlayout->setMargin(0);
    m_vlayout->setSpacing(20);

    QWidget *w = new QWidget;
    w->setLayout(m_vlayout);

    m_baseMainLayout->addWidget(w);
}

CategoryWidget::~CategoryWidget()
{
//    QList<InfoCard *> items = findChildren<InfoCard*>();
//    for (InfoCard *item : items) {
//        m_infoGroup->removeItem(item);
//        item->deleteLater();
//    }

    QLayoutItem *child;
    while ((child = m_vlayout->takeAt(0)) != 0) {
      InfoCard* item = qobject_cast<InfoCard*>(child->widget());
      if(item)
          item->deleteLater();
      delete child;
    }
}

void CategoryWidget::setInfo(const StringMap &result)
{
    int num = 1;
    if (num == 1) {
        InfoCard *card = new InfoCard(this->objectName(), this);
        card->setTitleVisible(false);
        card->setInfo(result);
        m_vlayout->addWidget(card);
    }
    else {
        for (int i = 0; i <= num; i++) {
            InfoCard *card = new InfoCard(this->objectName(), this);
            card->setTitleVisible(true);
            card->setInfo(result);
            m_vlayout->addWidget(card);
        }
    }
}

//test multi memory
void CategoryWidget::setInfo2(const StringMap &result)
{
    int num = 2;
    for (int i = 0; i < num; i++) {
        InfoCard *card = new InfoCard(this->objectName(), this);
        card->setTitleVisible(true);
        card->setInfo(result);
        m_vlayout->addWidget(card);
    }
}
