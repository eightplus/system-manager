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

#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <QMap>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QButtonGroup;
class QAbstractButton;
class QLabel;
class PushButton;
QT_END_NAMESPACE

class ContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContentWidget(QWidget *parent = nullptr);
    ~ContentWidget();

    void loadButtonsAndWidgets();

private slots:
    void updateCurrentWidget(const int index);
    void updateCurrentIcon(const int index);

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    QVBoxLayout *m_leftLayout;
    QVBoxLayout *m_rightLayout;
    QButtonGroup *m_buttonGroup;
    QMap<QAbstractButton*, QString> m_titleMap;
    QMap<int, QWidget*> m_widgetMap;
    QStringList m_iconList;
    PushButton * m_currentBtn;
    QWidget *m_currentWidget;
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    int m_index;
};

#endif // CONTENTWIDGET_H
