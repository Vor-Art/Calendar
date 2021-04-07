TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += \
        Sources/calendar.cpp \
        Sources/date.cpp \
        main.cpp

HEADERS += \
    Headers/calendar.h \
    Headers/date.h
