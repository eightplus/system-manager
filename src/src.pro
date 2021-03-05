#-------------------------------------------------
#
# Project created by QtCreator 2019-12-14T00:48:46
#
#-------------------------------------------------

include(../interface/interface.pri)

QT      += gui core dbus network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = momo-system-manager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

target.source  += $$TARGET
target.path = /usr/bin
INSTALLS += target

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14
CONFIG += qt warn_on
CONFIG += release
CONFIG += link_pkgconfig
#PKGCONFIG += geoip

LIBS += -lGeoIP -lX11

QMAKE_CPPFLAGS *= $(shell dpkg-buildflags --get CPPFLAGS)
QMAKE_CFLAGS   *= $(shell dpkg-buildflags --get CFLAGS)
QMAKE_CXXFLAGS *= $(shell dpkg-buildflags --get CXXFLAGS)
QMAKE_LFLAGS   *= $(shell dpkg-buildflags --get LDFLAGS)
QMAKE_CFLAGS_DEBUG += -g

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    basewidget.cpp \
    copyrightwidget.cpp \
    aboutwidget.cpp \
    mybottomwidget.cpp \
    propertywidget.cpp \
    categorywidget.cpp \
    infocard.cpp \
    infoitems.cpp \
    infogroup.cpp \
    logowidget.cpp \
    linewidget.cpp \
    toolwidget.cpp \
    label.cpp \
    toolbutton.cpp \
    pushbutton.cpp \
    systembutton.cpp \
    ipworker.cpp \
    confirmdialog.cpp \
    threadmodule.cpp \
    topwidget.cpp \
    bottomwidget.cpp \
    titlebuttongroup.cpp \
    readmewidget.cpp \
    authorwidget.cpp \
    infoframe.cpp \
    monitorframe.cpp \
    cleanframe.cpp \
    toptoolbar.cpp \
    homepage.cpp \
    navigationbutton.cpp \
    monitor/monitorbutton.cpp \
#    monitor/processscrollareaframe.cpp \
    monitor/protest1.cpp \
    monitor/protest2.cpp \
    monitor/titleheader.cpp \
    monitor/memorymonitor.cpp \
    monitor/memorywidget.cpp \
    monitor/cpumonitor.cpp \
    monitor/cpuwidget.cpp \
    monitor/diskmonitor.cpp \
    monitor/diskwidget.cpp \
    monitor/processmonitor.cpp \
    monitor/processwidget.cpp \
    monitor/networkmonitor.cpp \
    monitor/networkwidget.cpp \
    monitor/iomonitor.cpp \
    monitor/iowidget.cpp \
    monitor/temperaturemonitor.cpp \
    monitor/temperaturewidget.cpp \
    monitor/monitorbasewidget.cpp \
    monitor/monitorworkerthread.cpp \
    clean/cleanertoolbar.cpp \
    clean/cleanertoolbutton.cpp \
    clean/cacheframe.cpp \
    clean/cookieframe.cpp \
    clean/historyframe.cpp \
    info/deviceframe1.cpp \
    info/deviceframe2.cpp \
    info/deviceframe3.cpp \
    info/infoscrollpanel.cpp \
    toolsframe.cpp \
    tools/pluginloader.cpp \
    basescrollwidget.cpp \
    extensionedgewidget.cpp \
    rightpanel.cpp

HEADERS += \
    mainwindow.h \
    basewidget.h \
    copyrightwidget.h \
    aboutwidget.h \
    mybottomwidget.h \
    propertywidget.h \
    categorywidget.h \
    infocard.h \
    infoitems.h \
    infogroup.h \
    logowidget.h \
    linewidget.h \
    toolwidget.h \
    utils.h \
    label.h \
    pushbutton.h \
    toolbutton.h \
    systembutton.h \
    ipworker.h \
    confirmdialog.h \
    threadmodule.h \
    topwidget.h \
    bottomwidget.h \
    titlebuttongroup.h \
    readmewidget.h \
    authorwidget.h \
    infoframe.h \
    monitorframe.h \
    cleanframe.h \
    toptoolbar.h \
    homepage.h \
    navigationbutton.h \
    monitor/monitorbutton.h \
#    monitor/processscrollareaframe.h \
    monitor/protest1.h \
    monitor/protest2.h \
    monitor/titleheader.h \
    monitor/memorymonitor.h \
    monitor/memorywidget.h \
    monitor/cpumonitor.h \
    monitor/cpuwidget.h \
    monitor/diskmonitor.h \
    monitor/diskwidget.h \
    monitor/processmonitor.h \
    monitor/processwidget.h \
    monitor/networkmonitor.h \
    monitor/networkwidget.h \
    monitor/iomonitor.h \
    monitor/iowidget.h \
    monitor/temperaturemonitor.h \
    monitor/temperaturewidget.h \
    monitor/monitorbasewidget.h \
    monitor/monitorworkerthread.h \
    clean/cleanertoolbar.h \
    clean/cleanertoolbutton.h \
    clean/cacheframe.h \
    clean/cookieframe.h \
    clean/historyframe.h \
    info/deviceframe1.h \
    info/deviceframe2.h \
    info/deviceframe3.h \
    info/infoscrollpanel.h \
    toolsframe.h \
    tools/pluginloader.h \
    contants.h \
    basescrollwidget.h \
    extensionedgewidget.h \
    rightpanel.h

RESOURCES += \
    res.qrc

unix {
    UI_DIR = $$PWD/.ui
    MOC_DIR = $$PWD/.moc
    OBJECTS_DIR = $$PWD/.obj
    RCC_DIR = $$PWD/.rcc
}
