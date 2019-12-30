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

#include "welcomepate.h"
#include "utils.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>

WelcomePage::WelcomePage(QWidget *parent)
    : QWidget(parent)
    , m_cancelBtn(new QPushButton)
{
    this->setObjectName("WelcomePage");
    if (parent) {
        this->setFixedSize(parent->size());
    }
    else {
        this->setFixedSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    }

    m_cancelBtn->setText(tr("Cancel"));
    m_cancelBtn->setVisible(false);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addStretch();
    mainLayout->addWidget(m_cancelBtn);
    mainLayout->addStretch();
    mainLayout->setSpacing(20);
    this->setLayout(mainLayout);

    connect(m_cancelBtn, &QPushButton::clicked, qApp, &QApplication::quit);
}
