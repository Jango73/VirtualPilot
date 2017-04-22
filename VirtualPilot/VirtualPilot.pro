#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T20:41:20
#
#-------------------------------------------------

QT += core gui network opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VirtualPilot
TEMPLATE = app
INCLUDEPATH += $$PWD/../Quick3D/Source
DEPENDPATH += $$PWD/../Quick3D

# C++ Flags
QMAKE_CXXFLAGS += -Wno-invalid-offsetof
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-reorder

# Libraries
CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Quick3D/release/ -lQuick3D
else:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Quick3D/debug/ -lQuick3D

# Code
SOURCES += \
    VirtualPilot.cpp \
    main.cpp

HEADERS  += \
    VirtualPilot.h

DISTFILES +=

RESOURCES += \
    VirtualPilot.qrc

FORMS += \
    VirtualPilot.ui
