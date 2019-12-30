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

#ifndef COPYRIGHTWIDGET_H
#define COPYRIGHTWIDGET_H

#include "basewidget.h"

QT_BEGIN_NAMESPACE
class InfoGroup;
QT_END_NAMESPACE

class CopyrightWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit CopyrightWidget();
    ~CopyrightWidget();

public slots:
    void addItem(const QString &title, const QString &value);
    void removeItem(const QString &title);

private:
    InfoGroup *m_infoGroup;
};

#endif // COPYRIGHTWIDGET_H
