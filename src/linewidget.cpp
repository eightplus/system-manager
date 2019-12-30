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

#include "linewidget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QMouseEvent>

LineWidget::LineWidget(QFrame *parent)
    : QFrame(parent)
    , m_titleLabel(new QLabel)
    , m_valueLabel(new QLabel)
    , m_btn(new QPushButton)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(15);
    mainLayout->setMargin(0);
    m_valueLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_valueLabel->setWordWrap(true);

    mainLayout->setContentsMargins(20, 2, 10, 2);
    mainLayout->addWidget(m_titleLabel);
    mainLayout->addWidget(m_valueLabel);
    mainLayout->addStretch();
    mainLayout->addWidget(m_btn);
    m_btn->setVisible(false);
    this->setLayout(mainLayout);
//    this->setFixedHeight(36);

    connect(m_btn, &QPushButton::clicked, this, &LineWidget::clicked);
}

void LineWidget::setTitle(const QString &title)
{
    m_titleLabel->setText(title);
    this->setAccessibleName(title);
}

void LineWidget::setValue(const QString &value)
{
    m_valueLabel->setText(value);
}

void LineWidget::setButtonVisible(bool b)
{
    m_btn->setVisible(b);
}

/*void LineWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QFrame::mousePressEvent(event);

    if (event->button() != Qt::LeftButton) {
        return;
    }

    emit clicked();
}*/

