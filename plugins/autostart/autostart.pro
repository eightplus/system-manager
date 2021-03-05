include(../../interface/interface.pri)

PLUGIN_NAME 	= autostart

QT              += widgets
TEMPLATE         = lib
CONFIG          += plugin c++14 link_pkgconfig

TARGET          = $$qtLibraryTarget($$PLUGIN_NAME)
DESTDIR          = $$_PRO_FILE_PWD_/../
DISTFILES       += $$PLUGIN_NAME.json

HEADERS += \
    autostartmanager.h \
    autostartwidget.h \
    autostartview.h \
    autostartmodel.h \
    autostartdelegate.h \
    plugininterface.h

SOURCES += \
    autostartmanager.cpp \
    autostartwidget.cpp \
    autostartview.cpp \
    autostartmodel.cpp \
    autostartdelegate.cpp

target.path = $${PREFIX}/lib/momo-system-manager/plugins/
INSTALLS += target

RESOURCES += \
    img.qrc
