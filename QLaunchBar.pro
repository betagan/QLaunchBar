#-------------------------------------------------
#
# Project created by QtCreator 2012-09-17T11:04:31
#
#-------------------------------------------------

QT       += core gui

TARGET = QLaunchBar
TEMPLATE = app


SOURCES += main.cpp\
        sidebarwidget.cpp \
    launchbutton.cpp \
    Settings/settingswidget.cpp \
    Settings/launchentrysettingswidget.cpp \
    Settings/generalsettingswidget.cpp \
    Settings/updatesettingswidget.cpp

HEADERS  += sidebarwidget.h \
    launchbutton.h \
    Settings/settingswidget.h \
    Settings/launchentrysettingswidget.h \
    Settings/generalsettingswidget.h \
    Settings/updatesettingswidget.h

FORMS    +=

RESOURCES += \
    DefaultIcons.qrc

OTHER_FILES += \
    README \
    COPYRIGHT
