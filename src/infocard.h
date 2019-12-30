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

#ifndef INFOCARD_H
#define INFOCARD_H

#include <QFrame>
#include "utils.h"

QT_BEGIN_NAMESPACE
class InfoGroup;
class InfoItems;
class QLabel;
QT_END_NAMESPACE

class InfoCard : public QFrame
{
    Q_OBJECT
public:
    explicit InfoCard(const QString &name, QWidget *parent = nullptr);
    ~InfoCard();

    void setInfo(const StringMap &result);
    void setTitleVisible(const bool b);

private:
    InfoGroup *m_infoGroup;
    InfoItems *m_infoItems;
    QLabel *m_titleLabel;
    QString m_name;
};

#endif // INFOCARD_H
