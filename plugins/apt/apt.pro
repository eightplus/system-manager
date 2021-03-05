include(../../interface/interface.pri)

PLUGIN_NAME 	= apt

QT              += widgets
TEMPLATE         = lib
CONFIG          += plugin c++14 link_pkgconfig

TARGET          = $$qtLibraryTarget($$PLUGIN_NAME)
DESTDIR          = $$_PRO_FILE_PWD_/../
DISTFILES       += $$PLUGIN_NAME.json

HEADERS += \
    aptmanager.h \
    aptwidget.h \
    selectfileframe.h \
    installframe.h \
    uninstallframe.h

SOURCES += \
    aptmanager.cpp \
    aptwidget.cpp \
    selectfileframe.cpp \
    installframe.cpp \
    uninstallframe.cpp

target.path = $${PREFIX}/lib/momo-system-manager/plugins/
INSTALLS += target
