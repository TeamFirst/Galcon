#-------------------------------------------------
#
# Project created by QtCreator 2011-05-30T18:44:01
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_unittestfinaltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_unittestfinaltest.cpp \
    ../Planet.cpp \
    ../Fleet.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../Planet.h \
    ../Fleet.h
