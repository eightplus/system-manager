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

#include "propertywidget.h"
#include "basewidget.h"
#include "categorywidget.h"
#include "copyrightwidget.h"
#include "threadmodule.h"

#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QThread>
#include <QDebug>

PropertyWidget::PropertyWidget(QWidget *parent)
    : BaseScrollWidget(parent)
    , m_refreshBtn(new QPushButton)
    , m_pageCounts(0)
{
    setTitle(tr("Property Page"));

    qRegisterMetaType<StringMap>("StringMap");

    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(Qt::red));
    this->setPalette(palette);



    m_refreshBtn->setStyleSheet("QPushButton{background-color:transparent;border: none;}");
    m_refreshBtn->setFocusPolicy(Qt::NoFocus);
    m_refreshBtn->setCursor(Qt::PointingHandCursor);
    m_refreshBtn->setFixedSize(32, 32);
    QPixmap pixmap(":/res/refresh.png");
    m_refreshBtn->setIcon(pixmap);
    m_refreshBtn->setIconSize(pixmap.size());
    m_refreshBtn->setToolTip(tr("Refresh"));

    m_layout->addWidget(m_refreshBtn);

    // init thread module
    m_threadModule = new ThreadModule;
    m_thread = new QThread(this);
    m_threadModule->moveToThread(m_thread);
    m_thread->start();
    connect(this, &PropertyWidget::requesetScanSystemInfo, m_threadModule, &ThreadModule::scanSystemInfo);
    connect(m_threadModule, &ThreadModule::sendSystemInfo, this, &PropertyWidget::onReceiveSystemInfo, Qt::QueuedConnection);
//    connect(m_threadModule, &ThreadModule::scanFinished, this, &PropertyWidget::scanFinished);
    connect(m_refreshBtn, &QPushButton::clicked, this, [=] () {
        this->doWork();
    });

    this->doWork();
}

QString PropertyWidget::title()
{
    return m_titleLabel->text();
}

void PropertyWidget::setTitle(const QString &title)
{
    m_titleLabel->setText(title);
    setAccessibleName(title);
}

PropertyWidget::~PropertyWidget()
{
    qDebug() << "PropertyWidget destory!!!";
    if (m_thread) {
        m_thread->quit();
        m_thread->wait();
    }

//    if (m_displayWidget)
//        m_displayWidget->removeEventFilter(this);

    for (auto i(m_categoryWidgets.begin()); i != m_categoryWidgets.end(); ++i) {
        BaseWidget *w = qobject_cast<BaseWidget*>(i.value());
        if (w)
            w->deleteLater();
    }
    m_categoryWidgets.clear();
}

void PropertyWidget::doWork()
{
    //clear layout
    /*while (QLayoutItem *item = m_displayLayout->takeAt(0))
    {
        item->widget()->deleteLater();
        delete item;
    }*/

    for (auto item : m_categoryWidgets.values()) {
        /*m_displayLayout*/areaLayout->removeWidget(item);
        item->deleteLater();
    }
    m_categoryWidgets.clear();
    m_pageCounts = 0;

    CopyrightWidget *m_copyrightWidget = new CopyrightWidget;
    BaseWidget *w = qobject_cast<BaseWidget *>(m_copyrightWidget);
    /*m_displayLayout*/areaLayout->insertWidget(m_pageCounts++, w);
    m_categoryWidgets.insert("Copyright", w);

    emit this->requesetScanSystemInfo();
}

void PropertyWidget::onReceiveSystemInfo(const StringMap &info, int type)
{
    switch (type) {
    case Audio: {
        CategoryWidget *cw = new CategoryWidget("Audio");
        BaseWidget *w = qobject_cast<BaseWidget *>(cw);
        m_categoryWidgets.insert("Audio", w);
        /*m_displayLayout*/areaLayout->insertWidget(m_pageCounts++, cw);
        cw->setInfo(info/*, "Audio"*/);
        break;
    }
    case Battery: {
        CategoryWidget *cw = new CategoryWidget("Battery");
        BaseWidget *w = qobject_cast<BaseWidget *>(cw);
        m_categoryWidgets.insert("Battery", w);
        /*m_displayLayout*/areaLayout->insertWidget(m_pageCounts++, cw);
        cw->setInfo(info/*, "Battery"*/);
        break;
    }
    case Board: {
        CategoryWidget *cw = new CategoryWidget("Board");
        BaseWidget *w = qobject_cast<BaseWidget *>(cw);
        m_categoryWidgets.insert("Board", w);
        /*m_displayLayout*/areaLayout->insertWidget(m_pageCounts++, cw);
        cw->setInfo(info/*, "Board"*/);
        break;
    }
    case Cdrom: {
        CategoryWidget *cw = new CategoryWidget("Cdrom");
        BaseWidget *w = qobject_cast<BaseWidget *>(cw);
        m_categoryWidgets.insert("Cdrom", w);
        /*m_displayLayout*/areaLayout->insertWidget(m_pageCounts++, cw);
        cw->setInfo(info/*, "Cdrom"*/);
        break;
    }
    case Computer: {
        CategoryWidget *cw = new CategoryWidget("Computer");
        BaseWidget *w = qobject_cast<BaseWidget *>(cw);
        m_categoryWidgets.insert("Computer", w);
        /*m_displayLayout*/areaLayout->insertWidget(m_pageCounts++, cw);
        cw->setInfo(info/*, "Computer"*/);
        break;
    }
    case Cpu: {
        CategoryWidget *cw = new CategoryWidget("Cpu");
        BaseWidget *w = qobject_cast<BaseWidget *>(cw);
        m_categoryWidgets.insert("Cpu", w);
        /*m_displayLayout*/areaLayout->insertWidget(m_pageCounts++, cw);
        cw->setInfo(info/*, "Cpu"*/);
        break;
    }
    case Desktop: {
        CategoryWidget *cw = new CategoryWidget("Desktop");
        BaseWidget *w = qobject_cast<BaseWidget *>(cw);
        m_categoryWidgets.insert("Desktop", w);
        /*m_displayLayout*/areaLayout->insertWidget(m_pageCounts++, cw);
        cw->setInfo(info/*, "Desktop"*/);
        break;
    }
    case Driver: {
        CategoryWidget *cw = new CategoryWidget("Driver");
        BaseWidget *w = qobject_cast<BaseWidget *>(cw);
        m_categoryWidgets.insert("Driver", w);
        /*m_displayLayout*/areaLayout->insertWidget(m_pageCounts++, cw);
        cw->setInfo(info/*, "Driver"*/);
        break;
    }
    case Harddisk: {
        CategoryWidget *cw = new CategoryWidget("Harddisk");
        BaseWidget *w = qobject_cast<BaseWidget *>(cw);
        m_categoryWidgets.insert("Harddisk", w);
        /*m_displayLayout*/areaLayout->insertWidget(m_pageCounts++, cw);
        cw->setInfo(info/*, "Harddisk"*/);
        break;
    }
    case Memory: {
        CategoryWidget *cw = new CategoryWidget("Memory");
        BaseWidget *w = qobject_cast<BaseWidget *>(cw);
        m_categoryWidgets.insert("Memory", w);
        /*m_displayLayout*/areaLayout->insertWidget(m_pageCounts++, cw);
        cw->setInfo2(info/*, "Memory"*/);
        break;
    }
    case Monitor: {
        CategoryWidget *cw = new CategoryWidget("Monitor");
        BaseWidget *w = qobject_cast<BaseWidget *>(cw);
        m_categoryWidgets.insert("Monitor", w);
        /*m_displayLayout*/areaLayout->insertWidget(m_pageCounts++, cw);
        cw->setInfo(info/*, "Monitor"*/);
        break;
    }
    case Network: {
        CategoryWidget *cw = new CategoryWidget("Network");
        BaseWidget *w = qobject_cast<BaseWidget *>(cw);
        m_categoryWidgets.insert("Network", w);
        /*m_displayLayout*/areaLayout->insertWidget(m_pageCounts++, cw);
        cw->setInfo(info/*, "Network"*/);
        break;
    }
    case Sensor: {
        CategoryWidget *cw = new CategoryWidget("Sensor");
        BaseWidget *w = qobject_cast<BaseWidget *>(cw);
        m_categoryWidgets.insert("Sensor", w);
        /*m_displayLayout*/areaLayout->insertWidget(m_pageCounts++, cw);
        cw->setInfo(info/*, "Sensor"*/);
        break;
    }
    default:
        break;
    }
}
