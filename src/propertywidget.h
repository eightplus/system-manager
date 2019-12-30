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

class PropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertyWidget(QWidget *parent = nullptr);
    ~PropertyWidget();

    void initWhellAnimation();
    void stopScroll();
    void doWork();

public slots:
    void onReceiveSystemInfo(const StringMap &info, int type);

signals:
    void requesetScanSystemInfo();
//    void scanFinished(bool isFirst);

protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    QFrame *m_displayWidget;
    QVBoxLayout *m_displayLayout;

    QPushButton *m_refreshBtn;
    QLabel *m_title;
    QScrollArea *m_displayScrollArea;

    QPropertyAnimation *m_wheelAnimation;
    double m_speedTime;
    int m_speed;

    QMap<QString, BaseWidget *> m_categoryWidgets;
    bool m_touch;
    int m_pageCounts;

    ThreadModule *m_threadModule;
    QThread *m_thread;
};

#endif // PROPERTYWIDGET_H
