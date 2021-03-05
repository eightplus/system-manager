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
    : BaseScrollWidget(parent)
    , m_toolGroup(new InfoGroup)
{
    setTitle(tr("Tool Page"));

    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(Qt::green));
    this->setPalette(palette);

    m_toolGroup->setSpacing(5);
    areaLayout->addWidget(m_toolGroup);
    areaLayout->addStretch();

    this->initTools();
}


/*const */QString ToolWidget::title() /*const*/
{
    return m_titleLabel->text();
}

void ToolWidget::setTitle(const QString &title)
{
    m_titleLabel->setText(title);
    setAccessibleName(title);
}

ToolWidget::~ToolWidget()
{
    qDebug() << "ToolWidget destory!!!";
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
