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

#include "toolbutton.h"

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPushButton>
#include <QPainter>

ToolButton::ToolButton(QFrame *parent)
    : QFrame(parent)
    , m_actionBtn(new QPushButton(this))
    , m_titleLabel(new QLabel)
    , iconLabel(new QLabel)
    , m_descriptionLabel(new QLabel)
{
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#ffffff"));
    this->setPalette(palette);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(150);

//    m_actionBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_actionBtn->setGeometry(QRect(this->rect()));

    //让被label覆盖的btn在任何地方都能响应鼠标事件
    m_descriptionLabel->setParent(m_actionBtn);
    iconLabel->setParent(m_actionBtn);
    m_titleLabel->setParent(m_actionBtn);
    m_titleLabel->setStyleSheet("QLabel{font-size:13px;font-weight:bold;color:#666666;}");

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addStretch();
    vlayout->addWidget(m_titleLabel);
    vlayout->addWidget(m_descriptionLabel);
    vlayout->addStretch();
    vlayout->setSpacing(10);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(iconLabel);
    mainLayout->addLayout(vlayout);
    mainLayout->addStretch();
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 0, 20, 0);

    this->setLayout(mainLayout);
    this->setIcon();

    connect(m_actionBtn, &QPushButton::clicked, this, &ToolButton::clicked);
}

void ToolButton::setIcon()
{
    QSize sz = QSize(32,32);
    QPixmap pixmap(sz);
    pixmap.fill(Qt::transparent);

    QPainterPath painterPath;
    painterPath.addEllipse(QRect(0, 0, pixmap.width(), pixmap.height()));

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setClipPath(painterPath);
    painter.drawPixmap(0, 0, QPixmap(":/res/tool.png").scaled(sz, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setPixmap(pixmap);
}

void ToolButton::setTitle(const QString &title)
{
    m_titleLabel->setText(title);
    setAccessibleName(title);
}

void ToolButton::setDescription(const QString &description)
{
    m_descriptionLabel->setText(description);
}

void ToolButton::mouseReleaseEvent(QMouseEvent *event)
{
    QFrame::mousePressEvent(event);

    if (event->button() != Qt::LeftButton) {
        return;
    }

    emit clicked();
}
