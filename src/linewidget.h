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

#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QLabel>

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE

class LineWidget : public QFrame
{
    Q_OBJECT

public:
    explicit LineWidget(QFrame *parent = nullptr);

    inline QString title() const { return m_titleLabel->text(); }
    void setTitle(const QString& title);
    void setValue(const QString& value);
    void setButtonVisible(bool b);

protected:
    //void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:
    void clicked() const;

private:
    QLabel *m_titleLabel;
    QLabel *m_valueLabel;
    QPushButton *m_btn;
};

#endif // LINEWIDGET_H
