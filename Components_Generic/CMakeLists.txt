add_library(Components_Generic SHARED
    Source/Components_Generic.cpp
    Source/CAirportGenerator.cpp
    Source/CNavaidDatabase.cpp
    Source/CNavaidComponent.cpp
    Source/CAirport.cpp
    Source/CRunway.cpp
    Source/CNavaid.cpp
    Source/Components_Generic_Global.h
    Source/Components_Generic.h
    Source/Constants.h
    Source/CAirportGenerator.h
    Source/CNavaidDatabase.h
    Source/CNavaidComponent.h
    Source/CAirport.h
    Source/CRunway.h
    Source/CNavaid.h
)

target_compile_definitions(Components_Generic PRIVATE COMPONENTS_GENERIC_LIB)

target_include_directories(Components_Generic PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/Source"
)

target_link_libraries(Components_Generic PUBLIC
    Quick3D
    qt-plus
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Qt6::Xml
    Qt6::OpenGL
    Qt6::OpenGLWidgets
)

set_target_properties(Components_Generic PROPERTIES DEBUG_POSTFIX "d")

# Plugins load from <app dir>/Plugins (see CPluginLoader::pluginPath),
# same destination as Components_Generic.pro (bin/Plugins).
set_target_properties(Components_Generic PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/VirtualPilot/Plugins"
)
