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

#ifndef SYSTEMBUTTON_H
#define SYSTEMBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>

class SystemButton : public QPushButton
{
    Q_OBJECT
public:
    enum ButtonStatus{NORMAL, ENTER, PRESS};

    explicit SystemButton(QWidget *parent = nullptr);
    void loadPixmap(const QString &iconPath);

protected:
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QPixmap m_pixmap;
    ButtonStatus m_status;
    bool m_mousePressed;
    int m_width;
    int m_height;
};

#endif // SYSTEMBUTTON_H
