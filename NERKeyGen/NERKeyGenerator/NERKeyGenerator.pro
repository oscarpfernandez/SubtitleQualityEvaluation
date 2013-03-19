#-------------------------------------------------
#
# Project created by QtCreator 2013-03-15T16:47:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NERKeyGenerator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    utils.cpp \
    simplecrypt.cpp

HEADERS  += mainwindow.h \
    common.h \
    utils.h \
    simplecrypt.h

RC_FILE = app.rc

OTHER_FILES += \
    app.rc

RESOURCES += \
    resources.qrc
