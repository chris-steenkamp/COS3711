QT       += core gui widgets

TARGET = question01_lib
TEMPLATE = app

CONFIG += console

SOURCES += \
        main.cpp \
        getstudentdetails.cpp

HEADERS += \
        getstudentdetails.h \

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Validators/release/ -lValidators
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Validators/debug/ -lValidators

INCLUDEPATH += $$PWD/../Validators
DEPENDPATH += $$PWD/../Validators
