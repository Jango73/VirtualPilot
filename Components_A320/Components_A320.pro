
QT += core gui network opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
DEFINES += COMPONENTS_A320_LIB

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
DESTDIR = $$PWD/../bin/Plugins

# C++ Flags
QMAKE_CXXFLAGS += -Wno-invalid-offsetof
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-reorder

# Target
CONFIG(debug, debug|release) {
    TARGET = Components_A320d
} else {
    TARGET = Components_A320
}

# Libraries
CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../bin/Plugins/ -lComponents_Genericd
} else {
    LIBS += -L$$PWD/../bin/Plugins/ -lComponents_Generic
}

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
    Source/CAirbusADIRU.h \
    Source/CAirbusAOASensor.h \
    Source/CAirbusGearSensor.h \
    Source/CAirbusComponent.h \
    Source/CAirbusController.h \
    Source/CAirbusData.h \
    Source/CAirbusDataSupplier.h \
    Source/CAirbusCFDIU.h \
    Source/CAirbusDMC.h \
    Source/CAirbusMCDU.h \
    Source/CAirbusELAC.h \
    Source/CAirbusFAC.h \
    Source/CAirbusFADEC.h \
    Source/CAirbusFCC.h \
    Source/CAirbusFCU.h \
    Source/CAirbusElectricalPanel.h \
    Source/CAirbusFlightComputer.h \
    Source/CAirbusFlightPlan.h \
    Source/CAirbusFMGC.h \
    Source/CAirbusFWC.h \
    Source/CAirbusPitotPort.h \
    Source/CAirbusSEC.h \
    Source/CAirbusStaticPort.h \
    Source/Components_A320.h \
    Source/components_a320_global.h \
    Source/Constants.h

SOURCES += \
    Source/CAirbusADIRU.cpp \
    Source/CAirbusAOASensor.cpp \
    Source/CAirbusGearSensor.cpp \
    Source/CAirbusComponent.cpp \
    Source/CAirbusController.cpp \
    Source/CAirbusData.cpp \
    Source/CAirbusDataSupplier.cpp \
    Source/CAirbusCFDIU.cpp \
    Source/CAirbusDMC.cpp \
    Source/CAirbusDMC_EWD.cpp \
    Source/CAirbusDMC_ND.cpp \
    Source/CAirbusDMC_PFD.cpp \
    Source/CAirbusDMC_SD.cpp \
    Source/CAirbusMCDU.cpp \
    Source/CAirbusELAC.cpp \
    Source/CAirbusFAC.cpp \
    Source/CAirbusFADEC.cpp \
    Source/CAirbusFCC.cpp \
    Source/CAirbusFCU.cpp \
    Source/CAirbusElectricalPanel.cpp \
    Source/CAirbusFlightComputer.cpp \
    Source/CAirbusFlightPlan.cpp \
    Source/CAirbusFMGC.cpp \
    Source/CAirbusFWC.cpp \
    Source/CAirbusPitotPort.cpp \
    Source/CAirbusSEC.cpp \
    Source/CAirbusStaticPort.cpp \
    Source/Components_A320.cpp

RESOURCES += \
    A320.qrc
