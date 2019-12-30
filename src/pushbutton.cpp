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

#include "pushbutton.h"

#include <QPainter>

PushButton::PushButton(QWidget *parent)
    : QPushButton(parent)
{
    setCheckable(true);
}

void PushButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    if (!isChecked())
        return;

    //Button的左边2px显示颜色为#00609a
    QRect r = rect();
    r.setRight(r.left() + 2);

    QPainter painter(this);
    painter.fillRect(r, QColor("#00609a"));
}
