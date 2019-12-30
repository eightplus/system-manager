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

#ifndef INFOITEMS_H
#define INFOITEMS_H

#include <QFrame>

#include "utils.h"

QT_BEGIN_NAMESPACE
class QFormLayout;
class QLabel;
QT_END_NAMESPACE

class InfoItems : public QFrame
{
    Q_OBJECT
public:
    explicit InfoItems(QWidget *parent = nullptr);
    ~InfoItems();

    void clearLayout(QLayout *layout);
    void setLogo();
    void setInfo(const StringMap &result);
    void addOneLine(const char *title, const QString &content);
    const QString myTrFunc(const char *str);
    QString transName(const QString &name);

private:
    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    QLabel *m_vendorIconLabel;
    QFormLayout *m_formLayout;
    int m_maxTitleLabelWidth;
    int m_maxFieldLabelWidth;

};

#endif // INFOITEMS_H
