cmake_minimum_required(VERSION 3.16)

project(VirtualPilot LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Network
    Xml
    OpenGL
    OpenGLWidgets
    SerialPort
    Multimedia
    Positioning
    Qml
    Test
)

find_package(ZLIB REQUIRED)

# Engine libraries from the Quick3D submodule, same versions as the
# Quick3D repository build (qt-plus, Jolt, Quick3D). quick3dtest is not
# built here: VirtualPilot only needs the engine libraries, and
# quick3dtest/CMakeLists.txt resolves Jolt through CMAKE_SOURCE_DIR,
# which only holds inside the Quick3D repository itself.
add_subdirectory(Quick3D/qt-plus)

# JoltPhysics (submodule Quick3D/third/JoltPhysics). Same settings as the
# Quick3D repository root: no LTO pushed into our scope, no install rules,
# no warnings, single precision, static objects linked into shared Quick3D.
set(INTERPROCEDURAL_OPTIMIZATION OFF)
set(ENABLE_INSTALL OFF)
set(ENABLE_ALL_WARNINGS OFF)
add_subdirectory(Quick3D/third/JoltPhysics/Build)
# Static Jolt objects link into the shared Quick3D library: require PIC.
set_target_properties(Jolt PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_subdirectory(Quick3D/quick3d)

add_subdirectory(Components_Generic)
add_subdirectory(Components_A320)
add_subdirectory(VirtualPilot)
