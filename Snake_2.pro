#-------------------------------------------------
#
# Project created by QtCreator 2019-09-01T22:18:38
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake_2
TEMPLATE = app


SOURCES += src/main.cpp\
        src/game.cpp \
    src/snake.cpp \
    src/tcp.cpp

HEADERS  += include/game.h \
    include/snake.h \
    include/tcp.h

RESOURCES += \
    resource.qrc
