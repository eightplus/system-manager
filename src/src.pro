#-------------------------------------------------
#
# Project created by QtCreator 2019-12-14T00:48:46
#
#-------------------------------------------------

QT      += gui core dbus network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = system-manager
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

LIBS += -lGeoIP

QMAKE_CPPFLAGS *= $(shell dpkg-buildflags --get CPPFLAGS)
QMAKE_CFLAGS   *= $(shell dpkg-buildflags --get CFLAGS)
QMAKE_CXXFLAGS *= $(shell dpkg-buildflags --get CXXFLAGS)
QMAKE_LFLAGS   *= $(shell dpkg-buildflags --get LDFLAGS)
QMAKE_CFLAGS_DEBUG += -g

SOURCES += \
    main.cpp \
    maindialog.cpp \
    welcomepate.cpp \
    basewidget.cpp \
    copyrightwidget.cpp \
    aboutwidget.cpp \
    contentwidget.cpp \
    bottomwidget.cpp \
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
    threadmodule.cpp

HEADERS += \
    maindialog.h \
    welcomepate.h \
    basewidget.h \
    copyrightwidget.h \
    aboutwidget.h \
    contentwidget.h \
    bottomwidget.h \
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
    threadmodule.h

RESOURCES += \
    res.qrc

unix {
    UI_DIR = $$PWD/.ui
    MOC_DIR = $$PWD/.moc
    OBJECTS_DIR = $$PWD/.obj
    RCC_DIR = $$PWD/.rcc
}
