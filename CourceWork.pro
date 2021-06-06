#-------------------------------------------------
#
# Project created by QtCreator 2021-05-20T09:08:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CourceWork
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
        cell.cpp \
        controller.cpp \
        enemy.cpp \
        enemy_view.cpp \
        main.cpp \
        player.cpp \
        player_view.cpp \
        widget.cpp

HEADERS += \
        avatar.h \
        cell.h \
        controller.h \
        enemy.h \
        enemy_view.h \
        player.h \
        player_view.h \
        widget.h


FORMS += \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32-msvc*{
    LIBS += -luser32
}
