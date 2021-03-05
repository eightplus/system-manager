include(../../interface/interface.pri)

PLUGIN_NAME 	= videorecorder

QT              += widgets
TEMPLATE         = lib
CONFIG          += plugin c++14 link_pkgconfig

TARGET          = $$qtLibraryTarget($$PLUGIN_NAME)
DESTDIR          = $$_PRO_FILE_PWD_/../
DISTFILES       += $$PLUGIN_NAME.json

HEADERS += \
    videomanager.h \
    videowidget.h

SOURCES += \
    videomanager.cpp \
    videowidget.cpp

target.path = $${PREFIX}/lib/momo-system-manager/plugins/
INSTALLS += target
