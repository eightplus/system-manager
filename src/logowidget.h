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

#ifndef LOGOWIDGET_H
#define LOGOWIDGET_H

#include <QLabel>

class LogoWidget : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(QString logo READ logo WRITE setLogo DESIGNABLE true SCRIPTABLE true)
public:
    explicit LogoWidget(QFrame *parent = nullptr);

    void setOS(const QString &os);
    void setCopyRight(const QString &copyright);
    void setLogo(const QString &logo);
    const QString logo() const { return m_logoLabel->text(); }

private:
    QLabel *m_logoLabel;
    QLabel *m_osLabel;
    QLabel *m_copyrightLabel;
};

#endif // LOGOWIDGET_H
