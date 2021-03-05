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

#include "mybottomwidget.h"
#include "ipworker.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>
#include <QEvent>
#include <QTimer>

MyBottomWidget::MyBottomWidget(QWidget *parent)
    : QWidget(parent)
    , m_iconLabel(new QLabel(this))
    , m_ipLabel(new QLabel(this))
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(20, 5, 20, 5);
    mainLayout->setSpacing(10);

    QPushButton *authorBtn = new QPushButton;
    authorBtn->setFocusPolicy(Qt::NoFocus);
    authorBtn->setText(tr("Author URI"));

    QList<QPushButton*> m_btnList;
    m_btnList << authorBtn;
//    foreach (QPushButton *button, m_btnList) {
//    }
    for (QPushButton *btn : m_btnList) {
        btn->installEventFilter(this);
        connect(btn, &QPushButton::clicked, this, &MyBottomWidget::onButtonClicked);
    }

    m_buttons[authorBtn] = "https://eightplus.github.io";

    m_ipLabel->setStyleSheet("QLabel{background-color: transparent;color: #000000;font-size: 12px;font-weight: medium;}");
    m_ipLabel->setAlignment(Qt::AlignRight);
    m_ipLabel->setWordWrap(true);
    m_ipLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(authorBtn, 0, Qt::AlignBottom  | Qt::AlignLeft);
    mainLayout->addStretch();
    mainLayout->addWidget(m_iconLabel, 0, Qt::AlignVCenter | Qt::AlignRight);
    mainLayout->addWidget(m_ipLabel, 0, Qt::AlignVCenter | Qt::AlignRight);

    this->setLayout(mainLayout);

    m_iconLabel->setVisible(false);
    QPixmap pixmap(":/res/ip.png");
    m_iconLabel->setPixmap(pixmap);
    m_iconLabel->setFixedSize(pixmap.size());

    //该线程如果网络监测异常，比较耗时时，将在用户关闭窗口时，进程无法退出
    //TODO:动态检查ip变化   /sys/class/net/wlp2s0/operstate  (up or down)
    /*IpWorker *m_thread = new IpWorker;
    connect(m_thread, &IpWorker::locationFinished, this, [=] (const QString &ip, const QString &city) {
        if (ip.isEmpty() || ip == "0.0.0.0") {
            m_ipLabel->clear();
            m_iconLabel->setVisible(false);
        }
        else {
            m_ipLabel->setText(QString("%1(%2)").arg(city).arg(ip));
            m_ipLabel->adjustSize();
            m_iconLabel->setVisible(true);
        }
    }, Qt::QueuedConnection);
    connect(m_thread, SIGNAL(finished()), m_thread, SLOT(deleteLater()), Qt::QueuedConnection);
    QTimer::singleShot(100, m_thread, [=] { m_thread->start(QThread::LowestPriority); });*/
}

void MyBottomWidget::onButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    Q_ASSERT(button);

    QDesktopServices::openUrl(QUrl(m_buttons[button], QUrl::TolerantMode));
}

bool MyBottomWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Enter) {
        setCursor(Qt::PointingHandCursor);
    }

    if (event->type() == QEvent::Leave) {
        setCursor(Qt::ArrowCursor);
    }

    return QWidget::eventFilter(watched, event);
}
