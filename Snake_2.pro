#-------------------------------------------------
#
# Project created by QtCreator 2019-09-01T22:18:38
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake_2
TEMPLATE = app


SOURCES += main.cpp\
        game.cpp \
    snake.cpp \
    tcp.cpp

HEADERS  += game.h \
    snake.h \
    tcp.h

RESOURCES += \
    resource.qrc
