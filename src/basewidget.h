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

#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLabel>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
QT_END_NAMESPACE

class BaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BaseWidget();
    ~BaseWidget();

    const QString title() const;
    void setTitle(const QString &title);

private:
    bool event(QEvent *event) Q_DECL_OVERRIDE;

protected:
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QVBoxLayout *m_baseMainLayout;
};

#endif // BASEWIDGET_H
