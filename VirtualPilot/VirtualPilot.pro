#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T20:41:20
#
#-------------------------------------------------

QT += core gui network opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# CONFIG += console

TARGET = VirtualPilot
TEMPLATE = app

INCLUDEPATH += $$PWD/../Quick3D/qt-plus/source/cpp
INCLUDEPATH += $$PWD/../Quick3D/qt-plus/source/cpp/Web
INCLUDEPATH += $$PWD/../Quick3D/Quick3D/Source
INCLUDEPATH += $$PWD/../Quick3D/Quick3D/Source/Animation
INCLUDEPATH += $$PWD/../Quick3D/Quick3D/Source/Base
INCLUDEPATH += $$PWD/../Quick3D/Quick3D/Source/Components
INCLUDEPATH += $$PWD/../Quick3D/Quick3D/Source/Input
INCLUDEPATH += $$PWD/../Quick3D/Quick3D/Source/Math
INCLUDEPATH += $$PWD/../Quick3D/Quick3D/Source/Mesh
INCLUDEPATH += $$PWD/../Quick3D/Quick3D/Source/Render
INCLUDEPATH += $$PWD/../Quick3D/Quick3D/Source/Terrain
INCLUDEPATH += $$PWD/../Quick3D/Quick3D/Source/Utils

DEPENDPATH += $$PWD/../Quick3D/Quick3D
DESTDIR = ../bin

# C++ Flags
QMAKE_CXXFLAGS += -Wno-invalid-offsetof
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-reorder

# Libraries
CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../Quick3D/Quick3D/bin/ -lQuick3Dd
} else {
    LIBS += -L$$PWD/../Quick3D/Quick3D/bin/ -lQuick3D
}

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../Quick3D/qt-plus/bin/ -lqt-plusd
} else {
    LIBS += -L$$PWD/../Quick3D/qt-plus/bin/ -lqt-plus
}

# Code
SOURCES += \
    Source/VirtualPilot.cpp \
    Source/main.cpp

HEADERS  += \
    Source/VirtualPilot.h

DISTFILES +=

FORMS += \
    Source/VirtualPilot.ui
