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

#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QLabel>

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE

class ToolButton : public QFrame
{
    Q_OBJECT

public:
    explicit ToolButton(QFrame *parent = nullptr);

    void setIcon();
    QString title() const { return m_titleLabel->text(); }
    void setTitle(const QString &title);
    void setDescription(const QString &description);

signals:
    void clicked() const;

protected:
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QPushButton *m_actionBtn;
    QLabel *iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_descriptionLabel;

    QString m_title;
    QString m_description;
};

#endif // TOOLBUTTON_H
