#-------------------------------------------------
#
# Project created by QtCreator 2012-10-23T15:07:39
#
#-------------------------------------------------

QT       += core gui phonon multimedia

TARGET = NERTool
TEMPLATE = app


SOURCES += main.cpp\
        nermainwindow.cpp \
    dragwidget.cpp \
    draglabel.cpp \
    about.cpp \
    xmlhandler.cpp \
    propertiestreewidget.cpp \
    nertablewidget.cpp \
    draglabelcomment.cpp \
    mediamngwidget.cpp \
    qcustomplot.cpp \
    nergraphwidget.cpp \
    utils.cpp \
    diff.cpp

HEADERS  += nermainwindow.h \
    dragwidget.h \
    draglabel.h \
    sleeper.h \
    about.h \
    xmlhandler.h \
    propertiestreewidget.h \
    nertablewidget.h \
    nercommon.h \
    draglabelcomment.h \
    mediamngwidget.h \
    qcustomplot.h \
    nergraphwidget.h \
    utils.h \
    diff.h

RC_FILE = app.rc

RESOURCES += \
    resource_items.qrc \
    resource_pics.qrc

OTHER_FILES += \
    app.rc \
    app.rc
