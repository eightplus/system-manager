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

#include "aboutwidget.h"
#include "label.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QLayoutItem>
#include <QScrollBar>
#include <QLabel>
#include <QIcon>

AboutWidget::AboutWidget(QWidget *parent)
    : QScrollArea(parent)
    , m_mainLayout(nullptr)
    , m_pixmap(QPixmap(QIcon::fromTheme("system-manager", QIcon(":/res/system-manager.png")).pixmap(QSize(64, 64))))
{
    this->setFrameStyle(QFrame::NoFrame);
    this->setWidgetResizable(true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->verticalScrollBar()->setContextMenuPolicy(Qt::PreventContextMenu);

    QFrame *mainFrame = new QFrame(this);
    mainFrame->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#ffffff"));
    mainFrame->setPalette(palette);
    m_mainLayout = new QVBoxLayout(mainFrame);
    m_mainLayout->setContentsMargins(10, 0, 10, 0);
    m_mainLayout->setSpacing(5);

    QLabel *m_logoLabel = new QLabel;
    m_logoLabel->setPixmap(m_pixmap);
    m_logoLabel->setFixedSize(m_pixmap.size());

    QLabel *m_nameLabel = new QLabel;
    m_nameLabel->setWordWrap(true);
    m_nameLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    m_nameLabel->setText(QString("%1 (%2)").arg(qApp->applicationName()).arg(qApp->applicationVersion()));
    QVBoxLayout *logo_layout = new QVBoxLayout;
    logo_layout->addWidget(m_logoLabel);
    logo_layout->addWidget(m_nameLabel);
    logo_layout->setSpacing(10);
    logo_layout->setContentsMargins(0, 0, 0, 0);
    logo_layout->setAlignment(m_logoLabel, Qt::AlignCenter);
    logo_layout->setAlignment(m_nameLabel, Qt::AlignCenter);

    m_mainLayout->addLayout(logo_layout);

    QLabel *h_separator = new QLabel();
    h_separator->setStyleSheet("QLabel{background:lightgray;}");
    h_separator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    h_separator->setFixedHeight(1);
    m_mainLayout->addSpacing(20);
    m_mainLayout->addWidget(h_separator);

    TitleLabel *copyrightLabel = new TitleLabel("Copyright © 2019-2020 lixiang, kobe24_lixiang@126.com");
    copyrightLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(copyrightLabel, Qt::AlignHCenter);

    QString txt = QString(tr("Code website:") + " " + this->linkWebsite("https://github.com/eightplus/system-manager") + "<br><br>" +
            tr("Developer's personal home page:") + " " + this->linkWebsite("https://eightplus.github.io") + "<br>");
    TitleLabel *sourceLabel = new TitleLabel(txt);
    sourceLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(sourceLabel, Qt::AlignHCenter);
    m_mainLayout->addStretch();

    this->setWidget(mainFrame);
}

AboutWidget::~AboutWidget()
{
    QLayoutItem *child;
    while ((child = m_mainLayout->takeAt(0)) != 0) {
      QLabel* item = qobject_cast<QLabel*>(child->widget());
      if (item)
          item->deleteLater();
      delete child;
    }
}

QString AboutWidget::linkWebsite(const QString &url, QString name)
{
    if (name.isEmpty()) {
        name = url;
    }

    return QString("<a href=\"" + url + "\">" + name + "</a>");
}

void AboutWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->verticalScrollBar()->setVisible(true);
}

void AboutWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->verticalScrollBar()->setVisible(false);
}
