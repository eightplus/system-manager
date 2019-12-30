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

#include "maindialog.h"
#include "welcomepate.h"
#include "contentwidget.h"
#include "systembutton.h"
#include "utils.h"

#include <QApplication>
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QScreen>
#include <QTimer>
#include <QDebug>

MainDialog::MainDialog(QWidget* parent, Qt::WindowFlags f)
	: QDialog(parent, f)
    , m_mousePressed(false)
    , m_stackedLayout(new QStackedLayout)
{
    this->setFixedSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAutoFillBackground(true);

    m_welcomeWidget = new WelcomePage(this);
    m_stackedLayout->addWidget(m_welcomeWidget);
    //m_stackedLayout->setCurrentWidget(m_welcomeWidget);

    m_contentWidget = new ContentWidget(this);
    m_stackedLayout->addWidget(m_contentWidget);
    m_stackedLayout->setCurrentWidget(m_contentWidget);

    QHBoxLayout *centralLayout = new QHBoxLayout;
    centralLayout->addLayout(m_stackedLayout);
    centralLayout->setSpacing(0);
    centralLayout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(centralLayout);

    m_clostBtn = new SystemButton(this);
    m_clostBtn->loadPixmap(":/res/close_button.png");
    m_clostBtn->move(this->rect().topRight() - QPoint(m_clostBtn->width(), 0));
    m_clostBtn->setVisible(true);
    m_clostBtn->raise();
    connect(m_clostBtn, &QPushButton::clicked, this, &QApplication::quit);

    this->moveCenter();
}

MainDialog::~MainDialog()
{

}

void MainDialog::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
        case Qt::Key_Escape:
            qApp->quit();
            break;
        default:
            break;
    }

    return QWidget::keyPressEvent(e);
}

void MainDialog::moveCenter()
{
    QPoint pos = QCursor::pos();
    QRect primaryGeometry;
    for (QScreen *screen : qApp->screens()) {
        if (screen->geometry().contains(pos)) {
            primaryGeometry = screen->geometry();
        }
    }

    if (primaryGeometry.isEmpty()) {
        primaryGeometry = qApp->primaryScreen()->geometry();
    }

    this->move(primaryGeometry.x() + (primaryGeometry.width() - this->width())/2,
               primaryGeometry.y() + (primaryGeometry.height() - this->height())/2);
    this->show();
    this->raise();
}

void MainDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->m_mousePressed = true;
    }

    QDialog::mousePressEvent(event);
}

void MainDialog::mouseReleaseEvent(QMouseEvent *event)
{
    this->m_mousePressed = false;

    QDialog::mouseReleaseEvent(event);
}

void MainDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (this->m_mousePressed) {
        move(event->globalPos() - this->m_dragPosition);
    }

    QDialog::mouseMoveEvent(event);
}
