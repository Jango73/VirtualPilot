
QT += core gui network opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
DEFINES += COMPONENTS_GENERIC_LIB

# Dependencies
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

# Directories
DESTDIR = $$PWD/../bin/Plugins
OBJECTS_DIR = $$PWD/obj
MOC_DIR = $$PWD/moc
RCC_DIR = $$PWD/rcc
UI_DIR = $$PWD/ui
MAKEFILE = $$PWD/make

# C++ Flags
QMAKE_CXXFLAGS += -Wno-invalid-offsetof
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-reorder

# Target
CONFIG(debug, debug|release) {
    TARGET = Components_Genericd
} else {
    TARGET = Components_Generic
}

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
HEADERS += \
    Source/Components_Generic_Global.h \
    Source/Components_Generic.h \
    Source/Constants.h \
    Source/CAirportGenerator.h \
    Source/CNavaidDatabase.h \
    Source/CNavaidComponent.h \
    Source/CAirport.h \
    Source/CRunway.h \
    Source/CNavaid.h

SOURCES += \
    Source/Components_Generic.cpp \
    Source/CAirportGenerator.cpp \
    Source/CNavaidDatabase.cpp \
    Source/CNavaidComponent.cpp \
    Source/CAirport.cpp \
    Source/CRunway.cpp \
    Source/CNavaid.cpp

# Copy qt-plus to bin
win32 {
    copyfile = $$PWD/../Quick3D/qt-plus/bin/*.dll
    copydest = $$PWD/../bin
} else {
    copyfile = $$PWD/../Quick3D/qt-plus/bin/*.so
    copydest = $$PWD/../bin
}

QMAKE_PRE_LINK += $$QMAKE_COPY $$quote($$shell_path($$copyfile)) $$quote($$shell_path($$copydest)) $$escape_expand(\\n\\t)

# Copy Quick3D to bin
win32 {
    copyfile = $$PWD/../Quick3D/Quick3D/bin/*.dll
    copydest = $$PWD/../bin
} else {
    copyfile = $$PWD/../Quick3D/Quick3D/bin/*.so
    copydest = $$PWD/../bin
}

QMAKE_PRE_LINK += $$QMAKE_COPY $$quote($$shell_path($$copyfile)) $$quote($$shell_path($$copydest)) $$escape_expand(\\n\\t)
