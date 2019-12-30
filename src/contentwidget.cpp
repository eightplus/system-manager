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

#include "contentwidget.h"
#include "bottomwidget.h"
#include "pushbutton.h"
#include "propertywidget.h"
#include "toolwidget.h"
#include "aboutwidget.h"

#include <QButtonGroup>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QEvent>
#include <QDebug>

namespace {
    const int LEFT_MAXWIDTH = 120;
    const int RIGHT_MAXWIDTH = MAIN_WINDOW_WIDTH - LEFT_MAXWIDTH;
    const int BOTTOM_MAXWIDTH = 46;
}

ContentWidget::ContentWidget(QWidget *parent)
    : QWidget(parent)
    , m_iconLabel(new QLabel(this))
    , m_titleLabel(new QLabel(this))
    , m_leftLayout(new QVBoxLayout)
    , m_rightLayout(new QVBoxLayout)
    , m_buttonGroup(new QButtonGroup)
    , m_currentBtn(nullptr)
    , m_currentWidget(nullptr)
    , m_index(-1)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    if (parent) {
        this->setFixedSize(parent->size());
    }
    else {
        this->setFixedSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    }

    m_buttonGroup->setExclusive(true);

    m_titleLabel->setStyleSheet("QLabel{background-color: transparent;color: #000000;font-size: 15px;font-weight: bold;}");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setFixedHeight(36);

    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->setMargin(0);
    contentLayout->setSpacing(0);

    m_leftLayout->setSpacing(0);
    m_leftLayout->setContentsMargins(0, 0, 0, 0);

    m_rightLayout->setSpacing(0);
    m_rightLayout->setContentsMargins(0, 0, 0, 0);

    QWidget *leftWidget = new QWidget;
    leftWidget->setObjectName("LeftContentWidget");
    leftWidget->setLayout(m_leftLayout);
    leftWidget->setFixedWidth(LEFT_MAXWIDTH);
    leftWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QWidget *rightWidget = new QWidget;
    rightWidget->setLayout(m_rightLayout);
    rightWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    contentLayout->addWidget(leftWidget);
    contentLayout->addWidget(rightWidget);

    BottomWidget *bottomWidget = new BottomWidget;
    bottomWidget->setFixedHeight(BOTTOM_MAXWIDTH);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_titleLabel, 0, Qt::AlignCenter);
    mainLayout->addLayout(contentLayout);
    mainLayout->addWidget(bottomWidget);
    this->setLayout(mainLayout);

    this->loadButtonsAndWidgets();
}

ContentWidget::~ContentWidget()
{
    m_titleMap.clear();
    m_iconList.clear();

    for (QWidget *btn : m_buttonGroup->buttons()) {
        btn->deleteLater();
    }

    for (auto widget : m_widgetMap.values()) {
        widget->deleteLater();
    }
    m_widgetMap.clear();
}

void ContentWidget::loadButtonsAndWidgets()
{
    int i = 0;

    /*------ PushButton的样式设置见style.qss中的 "QWidget#LeftContentWidget QPushButton" ------*/
    // property button
    PushButton *propertyBtn = new PushButton;
    propertyBtn->setText(tr("Property"));
    m_titleMap[propertyBtn] = tr("Property");
    m_buttonGroup->addButton(propertyBtn);
    connect(propertyBtn, &PushButton::clicked, this, [=] { updateCurrentWidget(i); });
    PropertyWidget *propertyWidget = new PropertyWidget(this);
    propertyWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_widgetMap[i++] = propertyWidget;
    m_iconList.append(":/res/property.png");

    // tool button
    PushButton *toolBtn = new PushButton;
    toolBtn->setText(tr("Tool Box"));
    m_titleMap[toolBtn] = tr("Tool Box");
    m_buttonGroup->addButton(toolBtn);
    connect(toolBtn, &PushButton::clicked, this, [=] { updateCurrentWidget(i); });
    ToolWidget *toolWidget = new ToolWidget(this);
    toolWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolWidget->hide();
    m_widgetMap[i++] = toolWidget;
    m_iconList.append(":/res/tool.png");

    // about button
    PushButton * aboutBtn = new PushButton;
    aboutBtn->setText(tr("About us"));
    m_titleMap[aboutBtn] = tr("About us");
    m_buttonGroup->addButton(aboutBtn);
    connect(aboutBtn, &PushButton::clicked, this, [=] { updateCurrentWidget(i); });
    AboutWidget *aboutWidget = new AboutWidget(this);
    aboutWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    aboutWidget->hide();
    m_widgetMap[i++] = aboutWidget;
    m_iconList.append(":/res/about.png");

    propertyBtn->setChecked(true);
    m_titleLabel->setText(m_titleMap[propertyBtn]);

    m_leftLayout->addWidget(m_iconLabel, 0, Qt::AlignHCenter);
    m_leftLayout->addSpacing(20);

    for (QWidget * w : m_buttonGroup->buttons()) {
        w->setFixedSize(120, 30);
        m_leftLayout->addWidget(w, 0, Qt::AlignLeft | Qt::AlignVCenter);
        w->installEventFilter(this);
    }
    m_leftLayout->addStretch();

    connect(m_buttonGroup, static_cast<void (QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked), this, [=] (QAbstractButton *btn) {
        PushButton *m_btn = qobject_cast<PushButton*>(btn);
        if (m_currentBtn) {
            m_currentBtn->setFixedSize(120, 30);
        }
        m_currentBtn = nullptr;
        m_currentBtn = m_btn;
        m_currentBtn->setFixedSize(120, 50);
        m_titleLabel->setText(m_titleMap[btn]);
    });

    m_currentBtn = propertyBtn;
    m_currentBtn->setFixedSize(120, 50);

    m_buttonGroup->buttons().first()->click();

    QIcon::setThemeName("ubuntu");
    this->updateCurrentIcon(0);
}

void ContentWidget::updateCurrentWidget(const int index)
{
    if (index == m_index) {
        return;
    }

    m_index = index;

    // 当m_currentWidget存在时，先从m_rightLayout清除，然后再加载新的页面进来
    if (m_currentWidget) {
        m_rightLayout->removeWidget(m_currentWidget);
        m_currentWidget->hide();
    }

    QTimer::singleShot(10, this, [=] {
        this->updateCurrentIcon(index);
        QWidget *widget = m_widgetMap[index];
        m_currentWidget = widget;
        m_currentWidget->setFixedSize(RIGHT_MAXWIDTH, this->height() - m_titleLabel->height() - BOTTOM_MAXWIDTH);
        m_rightLayout->addWidget(m_currentWidget, 0, Qt::AlignCenter);
        m_currentWidget->show();
    });
}

void ContentWidget::updateCurrentIcon(const int index)
{
    if (m_iconList.count() >= index) {
        QString iconPath = m_iconList.at(index);
        QPixmap pixmap = std::move(QIcon::fromTheme("system-manager", QIcon(iconPath)).pixmap(QSize(32, 32)));
        pixmap.setDevicePixelRatio(1.0);
        m_iconLabel->setPixmap(pixmap);
    }
}

bool ContentWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (qobject_cast<PushButton*>(watched) && event->type() == QEvent::KeyPress) {
        return true;
    }

    return false;
}
