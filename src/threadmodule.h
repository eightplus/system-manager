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

#ifndef THREADMODULE_H
#define THREADMODULE_H

#include <QObject>

#include "utils.h"

class ThreadModule : public QObject
{
    Q_OBJECT
public:
    explicit ThreadModule(QObject *parent = nullptr);
    ~ThreadModule();

public slots:
    void scanSystemInfo();

signals:
    void sendSystemInfo(const StringMap &info, int type);

private:
    bool m_isFirst;
};

#endif // THREADMODULE_H
