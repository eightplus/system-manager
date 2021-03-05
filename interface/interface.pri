DEFINES += QT_MESSAGELOGCONTEXT

HEADERS += \
    $$PWD/plugininterface.h \
    $$PWD/monitorinterface.h

SOURCES += \

INCLUDEPATH += $$PWD

isEmpty(PREFIX)
{
    PREFIX = /usr
}
