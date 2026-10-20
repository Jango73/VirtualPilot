add_executable(VirtualPilot
    Source/main.cpp
    Source/VirtualPilot.cpp
    Source/VirtualPilot.h
    Source/VirtualPilot.ui
)

target_include_directories(VirtualPilot PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Source"
)

target_link_libraries(VirtualPilot PRIVATE
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

set_target_properties(VirtualPilot PROPERTIES DEBUG_POSTFIX "d")

# Plugin file names carry the same debug suffix (see GENERIC_PLUGIN).
target_compile_definitions(VirtualPilot PRIVATE
    $<$<CONFIG:Debug>:VIRTUALPILOT_DEBUG_BUILD>
)

# Runtime data (scenes, vehicles, textures) resolves next to the binary
# (see CPluginLoader::pluginPath, applicationDirPath() + "/Vehicles");
# mirror bin/ beside the executable, same pattern as Quick3DTest.
add_custom_command(TARGET VirtualPilot POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/bin
        $<TARGET_FILE_DIR:VirtualPilot>
)
