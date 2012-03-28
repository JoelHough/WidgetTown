#-------------------------------------------------
#
# Project created by QtCreator 2012-03-26T04:02:43
#
#-------------------------------------------------

QT       += core gui

TARGET = WidgetTown
TEMPLATE = app


SOURCES += main.cpp\
    tilescene.cpp \
    character.cpp \
    characterview.cpp \
    customproxy.cpp \
    player.cpp

HEADERS  += \
    tilescene.h \
    character.h \
    Constants.h \
    characterview.h \
    customproxy.h \
    player.h

FORMS    += widgettown.ui

OTHER_FILES += \
    tileset.png \
    map.tmx \
    nerd.png

RESOURCES += \
    resources.qrc
