#-------------------------------------------------
#
# Project created by QtCreator 2012-10-23T15:07:39
#
#-------------------------------------------------

QT       += core gui

TARGET = NERTool
TEMPLATE = app


SOURCES += main.cpp\
        nermainwindow.cpp \
    dragwidget.cpp \
    draglabel.cpp \
    about.cpp \
    difftablewidget.cpp

HEADERS  += nermainwindow.h \
    dragwidget.h \
    draglabel.h \
    sleeper.h \
    about.h \
    difftablewidget.h

RC_FILE = app.rc

RESOURCES += \
    resource_items.qrc \
    resource_pics.qrc

OTHER_FILES += \
    app.rc
