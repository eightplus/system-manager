/*
 * Copyright (C) 2018 ~ 2020 kobe24_lixiang@126.com
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

#ifndef _MAIN_DIALOG_H_
#define _MAIN_DIALOG_H_

#include <QDialog>

QT_BEGIN_NAMESPACE
class QStackedLayout;
class QPushButton;
class TitleButton;
class WelcomePage;
class ContentWidget;
class SystemButton;
QT_END_NAMESPACE

class MainDialog : public QDialog
{
	Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = nullptr, Qt::WindowFlags f = 0);
    ~MainDialog();

    void moveCenter();

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QPoint m_dragPosition;
    bool m_mousePressed;
    QStackedLayout *m_stackedLayout;
    WelcomePage *m_welcomeWidget;
    ContentWidget *m_contentWidget;
    SystemButton *m_clostBtn;
};

#endif // _MAIN_DIALOG_H_
