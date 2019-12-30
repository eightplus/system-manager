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

#include "copyrightwidget.h"
#include "infogroup.h"
#include "utils.h"
#include "logowidget.h"
#include "linewidget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

CopyrightWidget::CopyrightWidget()
    : BaseWidget()
    , m_infoGroup(new InfoGroup)
{
    this->setObjectName("CopyRight");
    this->setTitle(tr("Version"));

    m_baseMainLayout->addWidget(m_infoGroup);

    LogoWidget *logo = new LogoWidget;
    logo->setOS("Ubuntu 16.04");
    logo->setCopyRight(tr("Copyright © 2019-2020 lixiang."));

    m_infoGroup->appendItem(logo);

    this->addItem(tr("Author:"), "lixiang");
}

CopyrightWidget::~CopyrightWidget()
{
    /*QList<LineWidget *> items = findChildren<LineWidget*>();
    for (LineWidget *item : items) {
        m_infoGroup->removeItem(item);
        item->deleteLater();
    }*/

    QLayoutItem *child;
    while ((child = m_infoGroup->layout()->takeAt(0)) != 0) {
      LineWidget *item = qobject_cast<LineWidget*>(child->widget());
      if(item)
          item->deleteLater();
      delete child;
    }

    if (m_infoGroup) {
        delete m_infoGroup;
        m_infoGroup = 0;
    }
}

void CopyrightWidget::addItem(const QString &title, const QString &value)
{
    LineWidget *w = new LineWidget;
    w->setButtonVisible(false);
    w->setTitle(title);
    w->setValue(value);
    m_infoGroup->appendItem(w);
    connect(w, &LineWidget::clicked, [=] {
        this->removeItem(w->title());
    });
}

void CopyrightWidget::removeItem(const QString &title)
{
    QList<LineWidget *> items = this->findChildren<LineWidget*>();
    for (LineWidget *item : items) {
        if (item->title() == title) {
            m_infoGroup->removeItem(item);
            item->deleteLater();
            break;
        }
    }
}
