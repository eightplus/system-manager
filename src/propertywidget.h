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

#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include <QFrame>
#include <QMap>

#include "utils.h"
#include "../basescrollwidget.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QScrollArea;
class QPropertyAnimation;
class QPushButton;
class QLabel;
class BaseWidget;
class ThreadModule;
class QThread;
QT_END_NAMESPACE

class PropertyWidget : public BaseScrollWidget
{
    Q_OBJECT

public:
    explicit PropertyWidget(QWidget *parent = 0);
    ~PropertyWidget();

    QString title() Q_DECL_OVERRIDE;
    void setTitle(const QString &title) Q_DECL_OVERRIDE;

    void doWork();

public slots:
    void onReceiveSystemInfo(const StringMap &info, int type);

signals:
    void requesetScanSystemInfo();

private:
    QPushButton *m_refreshBtn;
    QMap<QString, BaseWidget *> m_categoryWidgets;
    int m_pageCounts;

    ThreadModule *m_threadModule;
    QThread *m_thread;
};

#endif // PROPERTYWIDGET_H
