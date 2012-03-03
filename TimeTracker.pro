
#-------------------------------------------------
#
# Project created by QtCreator 2011-04-27T08:49:56
#
#-------------------------------------------------

QT       += core gui xml sql

TARGET = TimeTracker
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    preferenceswidget.cpp \
    projectwidget.cpp \
    trayiconcommand.cpp \
    preferences.cpp \
    project.cpp \
    timespan.cpp \
    createprojectdialog.cpp \
    screenshot.cpp \
    genericdao.cpp \
    debugutils.cpp \
    timetrackerapp.cpp \
    reportwidget.cpp

HEADERS  += mainwindow.h \
    preferenceswidget.h \
    projectwidget.h \
    trayiconcommand.h \
    preferences.h \
    project.h \
    timespan.h \
    createprojectdialog.h \
    screenshot.h \
    genericdao.h \
    debugutils.h \
    timetrackerapp.h \
    reportwidget.h

FORMS += mainwindow.ui \
    preferenceswidget.ui \
    projectwidget.ui \
    createprojectdialog.ui \
    reportwidget.ui

RESOURCES += \
    res.qrc

win32 {
}

macx-g++{
    ICON = images/timetracker.icns
}

win32:RC_FILE  += TimeTracker.rc










