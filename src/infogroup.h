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

#ifndef INFOGROUP_H
#define INFOGROUP_H

#include <QFrame>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QTimer;
QT_END_NAMESPACE

class InfoGroup : public QFrame
{
    Q_OBJECT

public:
    explicit InfoGroup(QFrame *parent = nullptr);
    ~InfoGroup();

    void insertItem(const int index, QFrame *item);
    void appendItem(QFrame *item);
    void removeItem(QFrame *item);
    void setSpacing(const int spaceing);
    int itemCount() const;

private slots:
    void updateHeight();

private:
    bool eventFilter(QObject *, QEvent *event) Q_DECL_OVERRIDE;

private:
    QVBoxLayout *m_layout;
    QTimer *m_timer;
};

#endif // INFOGROUP_H
