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

#include "threadmodule.h"

#include <QApplication>
#include <QDBusReply>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QThread>

ThreadModule::ThreadModule(QObject *parent) :
    QObject(parent)
    , m_isFirst(true)
{

}

ThreadModule::~ThreadModule()
{

}

void ThreadModule::scanSystemInfo()
{
    QDBusInterface *systemiface;
    systemiface = new QDBusInterface("com.kylin.assistant.systemdaemon",
                               "/com/kylin/assistant/systemdaemon",
                               "com.kylin.assistant.systemdaemon",
                               QDBusConnection::systemBus());

    StringMap m_info;

    /*QDBusReply*/QDBusPendingReply<QMap<QString, QVariant> > reply1 = systemiface->call("get_cpu_info");
    if (reply1.isError()) {
        return;
    }
    else {
        m_info = reply1.value();
    }

    emit sendSystemInfo(m_info, 5);
    m_info.clear();

    QDBusPendingReply<QMap<QString, QVariant> > reply2 = systemiface->call("get_computer_info");
    if (reply2.isError()) {
        return;
    }
    else {
        m_info = reply2.value();
    }

    emit sendSystemInfo(m_info, 4);
    m_info.clear();

    QDBusPendingReply<QMap<QString, QVariant> > reply3 = systemiface->call("get_board_info");
    if (reply3.isError()) {
        return;
    }
    else {
        m_info = reply3.value();
    }

    emit sendSystemInfo(m_info, 2);

    emit sendSystemInfo(m_info, 9);//test multi memory
    m_info.clear();

//    emit this->scanFinished(m_isFirst);
//    if (m_isFirst) {
//        m_isFirst = !m_isFirst;
//    }
}


