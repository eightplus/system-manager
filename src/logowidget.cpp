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

#include "logowidget.h"

#include <QVBoxLayout>

LogoWidget::LogoWidget(QFrame *parent)
    :QFrame(parent)
    , m_logoLabel(new QLabel(this))
    , m_osLabel(new QLabel(this))
    , m_copyrightLabel(new QLabel(this))
{
    m_osLabel->adjustSize();
    m_osLabel->setAlignment(Qt::AlignLeft);
    m_copyrightLabel->adjustSize();
    m_copyrightLabel->setAlignment(Qt::AlignLeft);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(m_osLabel);
    vlayout->addWidget(m_copyrightLabel);
    vlayout->addStretch();
    vlayout->setSpacing(5);
    vlayout->setMargin(0);
    vlayout->setAlignment(m_osLabel, Qt::AlignLeft | Qt::AlignTop);
    vlayout->setAlignment(m_copyrightLabel, Qt::AlignLeft);

    QHBoxLayout *maniLayout = new QHBoxLayout;
    maniLayout->addLayout(vlayout);
    maniLayout->addStretch();
    maniLayout->addWidget(m_logoLabel);
    maniLayout->setSpacing(15);
    maniLayout->setContentsMargins(20, 0, 20, 0);
    maniLayout->setAlignment(m_logoLabel, Qt::AlignTop);
    this->setLayout(maniLayout);
}

void LogoWidget::setOS(const QString &os)
{
    m_osLabel->setText(os);
}

void LogoWidget::setCopyRight(const QString &copyright)
{
    m_copyrightLabel->setText(copyright);
}

void LogoWidget::setLogo(const QString &logo)
{
    m_logoLabel->setPixmap(QPixmap(logo));
}
