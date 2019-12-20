QT       += core gui widgets xml

TARGET = question04
TEMPLATE = app

CONFIG += console

SOURCES += \
    main.cpp \
    processstudent.cpp \
    student.cpp \
    studentlist.cpp \
    studentlistxmlwriter.cpp \
    studentlistxmlreader.cpp \
    studentlistxmldoc.cpp

HEADERS += \
    processstudent.h \
    student.h \
    studentlist.h \
    studentlistxmlwriter.h \
    studentlistxmlreader.h \
    studentlistxmldoc.h

DISTFILES += \
    question01.exe
