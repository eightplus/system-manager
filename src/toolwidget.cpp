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

#include "toolwidget.h"
#include "infogroup.h"
#include "toolbutton.h"
#include "confirmdialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QEvent>
#include <QSignalMapper>
#include <QScrollArea>
#include <QScrollBar>
#include <QProcess>
#include <QDebug>

ToolWidget::ToolWidget(QWidget *parent)
    : QWidget(parent)
    , m_scrollArea(new QScrollArea)
    , m_displayLayout(new QVBoxLayout)
    , m_displayWidget(new QFrame)
    , m_toolGroup(new InfoGroup)
//    , m_signalMapper(new QSignalMapper(this))
{
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#ffffff"));
    this->setPalette(palette);

    QLabel *label = new QLabel;
    label->setContentsMargins(20, 5, 0, 5);
    label->setText(tr("System tool"));

    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setFocusPolicy(Qt::NoFocus);
    m_scrollArea->setFrameStyle(QFrame::NoFrame);
    m_scrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    m_scrollArea->setContentsMargins(0, 0, 0, 0);
    m_scrollArea->viewport()->setBackgroundRole(QPalette::Light);
    m_scrollArea->viewport()->setAutoFillBackground(true);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    m_scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{margin:0px 0px 0px 0px;background-color:rgb(255,255,255,100);border:0px;width:10px;}\
//         QScrollBar::sub-line:vertical{subcontrol-origin:margin;border:1px solid red;height:13px}\
//         QScrollBar::up-arrow:vertical{subcontrol-origin:margin;background-color:blue;height:13px}\
//         QScrollBar::sub-page:vertical{background-color:#EEEDF0;}\
//         QScrollBar::handle:vertical{background-color:#D1D0D2;width:10px;} QScrollBar::handle:vertical:hover{background-color:#14ACF5;width:10px;}  QScrollBar::handle:vertical:pressed{background-color:#0B95D7;width:10px;}\
//         QScrollBar::add-page:vertical{background-color:#EEEDF0;}\
//         QScrollBar::down-arrow:vertical{background-color:yellow;}\
//         QScrollBar::add-line:vertical{subcontrol-origin:margin;border:1px solid green;height:13px}");
    m_displayLayout->setContentsMargins(0, 0, 20, 5);//20px的边距留给滑动条显示，避免滑动条盖住ToolButton的区域
    m_displayWidget->setLayout(m_displayLayout);
    m_scrollArea->setWidget(m_displayWidget);

    m_toolGroup->setSpacing(5);
    m_displayLayout->addWidget(m_toolGroup);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(label, 0, Qt::AlignLeft);
    centralLayout->addSpacing(20);
    centralLayout->addWidget(m_scrollArea, 0 , Qt::AlignHCenter);
    centralLayout->setContentsMargins(0, 5, 5, 0);
    centralLayout->setSpacing(0);
    this->setLayout(centralLayout);

    this->initTools();
}

ToolWidget::~ToolWidget()
{
    QList<ToolButton *> items = findChildren<ToolButton*>();
    for (ToolButton *item : items) {
        m_toolGroup->removeItem(item);
        item->deleteLater();
    }

    //qDeleteAll(m_toolItems);
    m_toolItems.clear();
}

void ToolWidget::initTools()
{
    QStringList nameList;
    nameList << tr("Reboot") << tr("Network restarted") << tr("Unlocked dpkg") << tr("Fix apt");
    QStringList descList;
    descList << tr("Reboots and checks integrity system") << tr("Network restarted or fix cancelled") <<
                tr("Unlocked /var/lib/dpkg/lock") << tr("Fix apt broken");
    for (int i = 0; i < nameList.length(); i++) {
        ToolButton *btn = new ToolButton;
        m_toolGroup->appendItem(btn);
        m_toolItems.append(btn);
        btn->setTitle(nameList.at(i));
        btn->setDescription(descList.at(i));
        //connect(btn, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
        //m_signalMapper->setMapping(btn, QString::number(i, 10));
        connect(btn, &ToolButton::clicked, this, &ToolWidget::onButtonClicked);
    }
    //connect(m_signalMapper, SIGNAL(mapped(QString)), this, SLOT(onMapperSelected(QString)));
}

void ToolWidget::onButtonClicked()
{
    ToolButton *btn = qobject_cast<ToolButton*>(sender());
    Q_ASSERT(btn);

//    QList<ToolButton *> items = findChildren<ToolButton*>();
//    for (ToolButton *item : items) {
//        if (btn->title() == item->title()) {
//            break;
//        }
//    }

    QString title = btn->title();
    if (title == tr("Reboot")) {
        ConfirmDialog dialog(tr("Confirm"),
                                tr("You're about to reboots and checks integrity system.") + "<br>"+
                                tr("This action cannot be undone. Are you sure you want to proceed?"), 0, QMessageBox::Yes | QMessageBox::No);
        if (dialog.exec() != -1) {
            if (dialog.standardButton(dialog.clickedButton()) == QMessageBox::Ok) {
                //        system("xterm -e '"
                //               "shutdown -Fr now"
                //               "; exec bash'");

//                QProcess::startDetached("systemctl", QStringList() << "restart" << "NetworkManager");

//                QProcess::startDetached("dbus-send --print-reply --dest=org.freedesktop.login1 /org/freedesktop/login1 org.freedesktop.login1.Manager.ScheduleShutdown");
            }
        }

    }
    else if (title == tr("Network restarted")) {
//        system("xterm -e '"
//               "sudo service network-manager restart"
//               " && "
//               "exit"
//               "; exec bash'");
    }
    else if (title == tr("Unlocked dpkg")) {
//        system("xterm -e '"
//               "sudo ./scripts/055.unlock_dpkg_lock"
//               " && "
//               "exit"
//               "; exec bash'");
    }
    else if (title == tr("Fix apt")) {
//        system("xterm -e '"
//               "sudo apt --fix-broken install"
//               " && "
//               "exit"
//               "; exec bash'");
    }
}

void ToolWidget::onMapperSelected(const QString &index)
{
    bool ok;
    int currentIndex = index.toInt(&ok, 10);
}

bool ToolWidget::event(QEvent *event)
{
    if (event->type() == QEvent::LayoutRequest) {
        setFixedHeight(m_displayLayout->sizeHint().height());
    }

    return QWidget::event(event);
}

void ToolWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_scrollArea->verticalScrollBar()->setVisible(true);
}

void ToolWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_scrollArea->verticalScrollBar()->setVisible(false);
}
