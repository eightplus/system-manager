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

#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QFrame>
#include "../basescrollwidget.h"

QT_BEGIN_NAMESPACE
class InfoGroup;
class ToolButton;
class QVBoxLayout;
class QScrollArea;
class QSignalMapper;
QT_END_NAMESPACE



class ToolWidget : public BaseScrollWidget
{
    Q_OBJECT

public:
    explicit ToolWidget(QWidget *parent = 0);
    ~ToolWidget();

    QString title() Q_DECL_OVERRIDE;
    void setTitle(const QString &title) Q_DECL_OVERRIDE;

    void initTools();

public slots:
    void onButtonClicked();
    void onMapperSelected(const QString &index);

private:
    InfoGroup *m_toolGroup;
    QFrame *m_displayWidget;
    QVBoxLayout *m_mainLayout = nullptr;
    QVBoxLayout *m_displayLayout = nullptr;
    QScrollArea *m_scrollArea = nullptr;
    QList<ToolButton *> m_toolItems;

};

#endif // TOOLWIDGET_H
