#-------------------------------------------------
#
# Project created by QtCreator 2018-09-16T20:40:59
#
#-------------------------------------------------

QT       += core gui

TARGET = Validators
TEMPLATE = lib

SOURCES += \
    modulecodevalidator.cpp \
    studentnumbervalidator.cpp

HEADERS += \
    modulecodevalidator.h \
    studentnumbervalidator.h

win32 {
    DEFINES += DATAOBJECTS_DLL
}
