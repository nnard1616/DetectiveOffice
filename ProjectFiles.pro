TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11
SOURCES += \
    Date.cpp \
    testDriver.cpp \
    case.cpp \
    client.cpp \
    UIDetectiveOffice.cpp \
    helperFunctions.cpp

HEADERS += \
    Date.h \
    client.h \
    case.h \
    UIDetectiveOffice.h \
    helperFunctions.h

