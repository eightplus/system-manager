include(../../interface/interface.pri)

PLUGIN_NAME 	= audiorecorder

QT              += widgets
TEMPLATE         = lib
CONFIG          += plugin c++14 link_pkgconfig

TARGET          = $$qtLibraryTarget($$PLUGIN_NAME)
DESTDIR          = $$_PRO_FILE_PWD_/../
DISTFILES       += $$PLUGIN_NAME.json

HEADERS += \
    audiomanager.h \
    audiowidget.h \
    resultwidget.h

SOURCES += \
    audiomanager.cpp \
    audiowidget.cpp \
    resultwidget.cpp

target.path = $${PREFIX}/lib/momo-system-manager/plugins/
INSTALLS += target
