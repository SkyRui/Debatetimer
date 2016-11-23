#-------------------------------------------------
#
# Project created by QtCreator 2016-09-30T19:22:13
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DebateTimer
TEMPLATE = app


SOURCES += main.cpp\
        mainview.cpp \
    loginui.cpp \
    countdown.cpp

HEADERS  += mainview.h \
    loginui.h \
    countdown.h

FORMS    += mainview.ui \
    loginui.ui
