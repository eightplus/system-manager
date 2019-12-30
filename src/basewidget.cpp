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

#include "basewidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QEvent>
#include <QDebug>

namespace {

static const char *templateHeaderIcon = "%1HeaderIconLabel";

}

BaseWidget::BaseWidget()
    : QWidget(nullptr)
{
    m_iconLabel = new QLabel;
    m_iconLabel->setFixedSize(16, 16);

    m_titleLabel = new QLabel;
    m_titleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_titleLabel->setObjectName("BaseHeaderTitle");//qss

    QLabel *h_separator = new QLabel(this);
    h_separator->setStyleSheet("QLabel{background:lightgray;}");
    h_separator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    h_separator->setFixedHeight(1);

    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->setSpacing(0);
    titleLayout->setContentsMargins(5, 0, 0, 0);
    titleLayout->addWidget(m_iconLabel, 0 , Qt::AlignLeft | Qt::AlignVCenter);
    titleLayout->addWidget(m_titleLabel, 0 , Qt::AlignLeft | Qt::AlignVCenter);
    titleLayout->addWidget(h_separator, 0, Qt::AlignVCenter);

    QFrame *headerWidget = new QFrame;
    headerWidget->setLayout(titleLayout);
    headerWidget->setStyleSheet("QFrame {padding: 0px 0;} QFrame:hover {background-color: rgba(169, 169, 169, 0.2);border-radius: 1px;}");

    m_baseMainLayout = new QVBoxLayout;
    m_baseMainLayout->addWidget(headerWidget);
    m_baseMainLayout->setSpacing(10);
    m_baseMainLayout->setMargin(0);

    this->setLayout(m_baseMainLayout);

    connect(this, &BaseWidget::objectNameChanged, [this] (const QString name) {
        qDebug() << "objectNameChanged:" << name << objectName();
        if (name == tr("CopyRight")) {
            m_iconLabel->setVisible(false);
            return;
        }
        m_iconLabel->setObjectName(QString(templateHeaderIcon).arg(objectName()));//qss设置图片
    });
}

BaseWidget::~BaseWidget()
{

}

const QString BaseWidget::title() const
{
    return m_titleLabel->text();
}

void BaseWidget::setTitle(const QString &title)
{
    m_titleLabel->setText(title);
    setAccessibleName(title);
}

bool BaseWidget::event(QEvent *event)
{
    if (event->type() == QEvent::LayoutRequest) {
        this->setFixedHeight(m_baseMainLayout->sizeHint().height());
    }

    return QWidget::event(event);
}
