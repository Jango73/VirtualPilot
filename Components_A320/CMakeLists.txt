add_library(Components_A320 SHARED
    Source/CAirbusADIRU.cpp
    Source/CAirbusAOASensor.cpp
    Source/CAirbusGearSensor.cpp
    Source/CAirbusComponent.cpp
    Source/CAirbusController.cpp
    Source/CAirbusData.cpp
    Source/CAirbusDataSupplier.cpp
    Source/CAirbusCFDIU.cpp
    Source/CAirbusDMC.cpp
    Source/CAirbusDMC_EWD.cpp
    Source/CAirbusDMC_ND.cpp
    Source/CAirbusDMC_PFD.cpp
    Source/CAirbusDMC_SD.cpp
    Source/CAirbusMCDU.cpp
    Source/CAirbusELAC.cpp
    Source/CAirbusFAC.cpp
    Source/CAirbusFADEC.cpp
    Source/CAirbusFCC.cpp
    Source/CAirbusFCU.cpp
    Source/CAirbusElectricalPanel.cpp
    Source/CAirbusFlightComputer.cpp
    Source/CAirbusFlightPlan.cpp
    Source/CAirbusFMGC.cpp
    Source/CAirbusFWC.cpp
    Source/CAirbusPitotPort.cpp
    Source/CAirbusSEC.cpp
    Source/CAirbusStaticPort.cpp
    Source/Components_A320.cpp
    Source/CAirbusADIRU.h
    Source/CAirbusAOASensor.h
    Source/CAirbusGearSensor.h
    Source/CAirbusComponent.h
    Source/CAirbusController.h
    Source/CAirbusData.h
    Source/CAirbusDataSupplier.h
    Source/CAirbusCFDIU.h
    Source/CAirbusDMC.h
    Source/CAirbusMCDU.h
    Source/CAirbusELAC.h
    Source/CAirbusFAC.h
    Source/CAirbusFADEC.h
    Source/CAirbusFCC.h
    Source/CAirbusFCU.h
    Source/CAirbusElectricalPanel.h
    Source/CAirbusFlightComputer.h
    Source/CAirbusFlightPlan.h
    Source/CAirbusFMGC.h
    Source/CAirbusFWC.h
    Source/CAirbusPitotPort.h
    Source/CAirbusSEC.h
    Source/CAirbusStaticPort.h
    Source/Components_A320.h
    Source/components_a320_global.h
    Source/Constants.h
    A320.qrc
)

target_compile_definitions(Components_A320 PRIVATE COMPONENTS_A320_LIB)

target_include_directories(Components_A320 PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/Source"
)

target_link_libraries(Components_A320 PUBLIC
    Components_Generic
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

set_target_properties(Components_A320 PROPERTIES DEBUG_POSTFIX "d")

# Plugins load from <app dir>/Plugins (see CPluginLoader::pluginPath),
# same destination as Components_A320.pro (bin/Plugins).
set_target_properties(Components_A320 PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/VirtualPilot/Plugins"
)
