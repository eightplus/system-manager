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

#include "systembutton.h"

SystemButton::SystemButton(QWidget *parent) :
    QPushButton(parent)
    , m_status(NORMAL)
    , m_mousePressed(false)
{
    this->setCursor(Qt::PointingHandCursor);
    this->setMouseTracking(false);
}

void SystemButton::loadPixmap(const QString &iconPath)
{
    m_pixmap = QPixmap(iconPath);
    m_width = m_pixmap.width()/3;
    m_height = m_pixmap.height();
    this->setFixedSize(m_width, m_height);
}

void SystemButton::loadPixmap(QString normal_icon, QString hover_icon, QString click_icon)
{
//    m_pixmap = QPixmap(iconPath);
//    m_width = m_pixmap.width()/3;
//    m_height = m_pixmap.height();
//    this->setFixedSize(m_width, m_height);

    m_pixmap = QPixmap(normal_icon);
    m_width = m_pixmap.width();
    m_height = m_pixmap.height();
    this->setFixedSize(m_width, m_height);
    m_normal_icon = normal_icon;
    m_hover_icon = hover_icon;
    m_click_icon = click_icon;

    setIcon(QIcon(m_normal_icon));
}

void SystemButton::enterEvent(QEvent *event)
{
//    m_status = ENTER;
//    this->update();

    setIcon(QIcon(m_hover_icon));
    QPushButton::enterEvent(event);
}

void SystemButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    if (event->button() == Qt::LeftButton) {
        m_mousePressed = true;
//        m_status = PRESS;
//        this->update();
    }
}

void SystemButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    if (m_mousePressed && this->rect().contains(event->pos())) {
        m_mousePressed = false;
//        m_status = ENTER;
//        this->update();
        setIcon(QIcon(m_click_icon));
        emit clicked();
    }
}

void SystemButton::leaveEvent(QEvent *event)
{
//    Q_UNUSED(event);
//    m_status = NORMAL;
//    this->update();
    setIcon(QIcon(m_normal_icon));
    QPushButton::enterEvent(event);
}

//void SystemButton::paintEvent(QPaintEvent *event)
//{
//    QPushButton::paintEvent(event);

//    QPainter painter;
//    painter.begin(this);
//    painter.drawPixmap(this->rect(), m_pixmap.copy(m_width * m_status, 0, m_width, m_height));
//    painter.end();
//}
