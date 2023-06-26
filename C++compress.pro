
QT       += core gui
QMAKE_CFLAGS += -std=c99
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = compress
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        trietree.cpp

HEADERS  += mainwindow.h \
    trietree.h

FORMS    += mainwindow.ui
