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

#include "label.h"

TitleLabel::TitleLabel(const QString &txt, QWidget *parent)
    : QLabel(txt, parent)
{
    QFont font;
    font.setPixelSize(12);
    setFont(font);
}

ContentLabel::ContentLabel(QWidget *parent)
    : QLabel(parent)
{
    QFont font;
    font.setPixelSize(12);
    setFont(font);
    setWordWrap(true);
}

void ContentLabel::resizeEvent(QResizeEvent *event)
{
    if (wordWrap() && sizePolicy().verticalPolicy() == QSizePolicy::Minimum) {
        setMinimumHeight(0);
        setMinimumHeight(heightForWidth(width()));
    }
    QLabel::resizeEvent(event);
}
