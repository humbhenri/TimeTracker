#-------------------------------------------------
#
# Project created by QtCreator 2012-01-18T15:54:19
#
#-------------------------------------------------

QT       += sql testlib xml

QT       -= gui

TARGET = tst_genericdaotest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += "../.."
HEADERS = ../../timespan.h \
    ../../genericdao.h \
    ../../debugutils.h

SOURCES = tst_genericdaotest.cpp \
    ../../timespan.cpp \
    ../../genericdao.cpp \
    ../../debugutils.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

