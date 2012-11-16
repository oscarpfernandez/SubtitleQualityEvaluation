#-------------------------------------------------
#
# Project created by QtCreator 2012-10-23T15:45:42
#
#-------------------------------------------------

QT       -= gui

TARGET = GoogleDiffMatch
TEMPLATE = lib

DEFINES += GOOGLEDIFFMATCH_LIBRARY

SOURCES += \
    diff_match_patch.cpp

HEADERS +=\
    diff_match_patch.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE29F97E3
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = GoogleDiffMatch.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

win32 {
    CONFIG += dll
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
