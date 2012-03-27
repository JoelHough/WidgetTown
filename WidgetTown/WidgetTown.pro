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
    tile.cpp \
    character.cpp \
    characterview.cpp

HEADERS  += \
    tilescene.h \
    tile.h \
    character.h \
    Constants.h \
    characterview.h

FORMS    += widgettown.ui

OTHER_FILES += \
    tileset.png \
    map.tmx

RESOURCES += \
    resources.qrc
