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

#include <QApplication>
#include <QFile>
#include <QTextCodec>
#include <QtDBus/QtDBus>
#include <QDebug>
#include <X11/Xlib.h>

#include <signal.h>
#include <unistd.h>

#include "mainwindow.h"

int getScreenWidth()
{
    Display *disp = XOpenDisplay(NULL);
    Screen *scrn = DefaultScreenOfDisplay(disp);
    if (NULL == scrn) {
        return 0;
    }
    int width = scrn->width;

    if (NULL != disp) {
        XCloseDisplay(disp);
    }

    return width;
}

inline bool checkRootUser()
{
    if (geteuid()) {
        return true;
    }

    qWarning() << "Don't run as root";

    return false;
}

int main(int argc, char *argv[])
{
    if (getScreenWidth() > 2560) {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    }

    signal(SIGINT, [](int) { QApplication::quit(); });// 设置退出信号

    qDebug() << "username:" << qgetenv("USER");

    QApplication app(argc, argv);
    app.setOrganizationName("eightplus");
    app.setApplicationName("system-manager");
    app.setApplicationVersion("1.0");
    app.setQuitOnLastWindowClosed(false);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif

#if QT_VERSION >= 0x040400
    // Enable icons in menus
    QCoreApplication::setAttribute(Qt::AA_DontShowIconsInMenus, false);
#endif

    if (!checkRootUser()) {
        return -1;
    }

    QFile qss(":/qss/style.qss");
    if (!qss.open(QIODevice::ReadOnly)) {
        qWarning("Can't open the style sheet file :/qss/style.qss.");
    }
    else {
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }

    MainWindow mw;
    mw.show();

    return app.exec();
}
