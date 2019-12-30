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

#ifndef CATEGORYWIDGET_H
#define CATEGORYWIDGET_H

#include <QPushButton>
#include <QVBoxLayout>

#include "utils.h"
#include "basewidget.h"

QT_BEGIN_NAMESPACE
class InfoGroup;
QT_END_NAMESPACE

class CategoryWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit CategoryWidget(const QString &name);
    ~CategoryWidget();

    void setInfo(const StringMap &result/*, const QString &name*/);
    void setInfo2(const StringMap &result);

private:
    InfoGroup *m_infoGroup;
    QVBoxLayout *m_vlayout;
};

#endif // CATEGORYWIDGET_H
