
#pragma once

//-------------------------------------------------------------------------------------------------
// Component class names

#define ClassName_CAirbusController         "CAirbusController"
#define ClassName_CAirbusStaticPort         "CAirbusStaticPort"
#define ClassName_CAirbusPitotPort          "CAirbusPitotPort"
#define ClassName_CAirbusAOASensor          "CAirbusAOASensor"
#define ClassName_CAirbusGearSensor         "CAirbusGearSensor"
#define ClassName_CAirbusEngineGenerator    "CAirbusEngineGenerator"
#define ClassName_CAirbusFlightComputer     "CAirbusFlightComputer"
#define ClassName_CAirbusADIRU              "CAirbusADIRU"
#define ClassName_CAirbusCFDIU              "CAirbusCFDIU"
#define ClassName_CAirbusDMC                "CAirbusDMC"
#define ClassName_CAirbusMCDU               "CAirbusMCDU"
#define ClassName_CAirbusELAC               "CAirbusELAC"
#define ClassName_CAirbusFAC                "CAirbusFAC"
#define ClassName_CAirbusFCC                "CAirbusFCC"
#define ClassName_CAirbusFADEC              "CAirbusFADEC"
#define ClassName_CAirbusFCU                "CAirbusFCU"
#define ClassName_CAirbusFMGC               "CAirbusFMGC"
#define ClassName_CAirbusFWC                "CAirbusFWC"
#define ClassName_CAirbusSEC                "CAirbusSEC"
#define ClassName_CAirbusElectricalPanel    "CAirbusElectricalPanel"

//-------------------------------------------------------------------------------------------------
// Parameter names

#define ParamName_ControlSurfaces           "ControlSurfaces"
#define ParamName_Engines                   "Engines"
#define ParamName_UnitIndex                 "UnitIndex"

//-------------------------------------------------------------------------------------------------
// Equipment names

#define EquipName_ADIRU                     "Air Data and Intertial Reference Unit"
#define EquipName_AOA                       "Angle of attack sensor"
#define EquipName_CFDS                      "Centralized Fault Display System"
#define EquipName_CFDIU                     "Centralized Fault Display Indicating Unit"
#define EquipName_DMC                       "Data Monitoring Computer"
#define EquipName_EFIS                      "Electronic Flight Instrument System"
#define EquipName_EGPWC                     "Enhanced Ground Proximity Warning Computer"
#define EquipName_EIS                       "Electronic Instrument System"
#define EquipName_ELAC                      "Elevator and Aileron Computer"
#define EquipName_FAC                       "Flight Augmentation Computer"
#define EquipName_FADEC                     "Full Authority Digital Engine Control"
#define EquipName_FCDC                      "Flight Control Data Concentrators"
#define EquipName_FCC                       "Flight Control Computer"
#define EquipName_FCU                       "Flight Control Unit"                       // Autopilot panel
#define EquipName_FMA                       "Flight Mode Annunciator"
#define EquipName_FMGC                      "Flight Management Guidance Computer"
#define EquipName_FMGS                      "Flight Management Guidance System"
#define EquipName_FWC                       "Flight Warning Computer"
#define EquipName_GPS                       "Global Positioning System"
#define EquipName_GPWS                      "Ground Proximity Warning System"
#define EquipName_IDG                       "Integrated Drive Generator"
#define EquipName_MCDU                      "Multipurpose Control and Display Unit"
#define EquipName_ND                        "Navigation Display"
#define EquipName_PFD                       "Primary Flight Display"
#define EquipName_PITOT                     "Pitot probe"
#define EquipName_RMP                       "Radio Management Panel"
#define EquipName_RAT                       "Ram Air Turbine"
#define EquipName_SEC                       "Spoilers and Elevator Computer"
#define EquipName_SI                        "Static Inverter"
#define EquipName_STATIC                    "Static probe"
#define EquipName_TAT                       "Total Air Temperature probe"
#define EquipName_TCAS                      "Traffic Alert and Collision Avoidance System"
#define EquipName_TR                        "Transformer Rectifier"

//-------------------------------------------------------------------------------------------------
// MCDU Strings

#define MCDU_CLEAR                          "CLEAR"

//-------------------------------------------------------------------------------------------------
// Q3D events

#define EventName_Jump500                   "JUMP_500"

#define EventName_FCU_AP1                   "FCU_AP1"
#define EventName_FCU_AP2                   "FCU_AP2"
#define EventName_FCU_ATHR                  "FCU_ATHR"
#define EventName_FCU_HDG_TRK               "FCU_HDG_TRK"
#define EventName_FCU_METRIC_ALT            "FCU_METRIC_ALT"
#define EventName_FCU_SPD_MACH              "FCU_SPD_MACH"
#define EventName_FCU_SEL_HEADING_INC       "FCU_SEL_HEADING_INC"
#define EventName_FCU_SEL_HEADING_DEC       "FCU_SEL_HEADING_DEC"
#define EventName_FCU_SEL_HEADING_INC_FAST  "FCU_SEL_HEADING_INC_FAST"
#define EventName_FCU_SEL_HEADING_DEC_FAST  "FCU_SEL_HEADING_DEC_FAST"

#define EventName_THR_THROTTLE_INC          "THR_THROTTLE_INC"
#define EventName_THR_THROTTLE_DEC          "THR_THROTTLE_DEC"

#define EventName_ELEC_GEN1                 "ELEC_GEN1"
#define EventName_ELEC_GEN2                 "ELEC_GEN2"
#define EventName_ELEC_APU_GEN              "ELEC_APU_GEN"
#define EventName_ELEC_AC_TIE               "ELEC_AC_TIE"
#define EventName_ELEC_IDG1                 "ELEC_IDG1"
#define EventName_ELEC_IDG2                 "ELEC_IDG2"
#define EventName_ELEC_BAT1                 "ELEC_BAT1"
#define EventName_ELEC_BAT2                 "ELEC_BAT2"
#define EventName_ELEC_AC_ESS_FEED          "ELEC_AC_ESS_FEED"

#define EventName_MCDU_CAPT_1L              "MCDU_CAPT_1L"
#define EventName_MCDU_CAPT_2L              "MCDU_CAPT_2L"
#define EventName_MCDU_CAPT_3L              "MCDU_CAPT_3L"
#define EventName_MCDU_CAPT_4L              "MCDU_CAPT_4L"
#define EventName_MCDU_CAPT_5L              "MCDU_CAPT_5L"
#define EventName_MCDU_CAPT_6L              "MCDU_CAPT_6L"
#define EventName_MCDU_CAPT_1R              "MCDU_CAPT_1R"
#define EventName_MCDU_CAPT_2R              "MCDU_CAPT_2R"
#define EventName_MCDU_CAPT_3R              "MCDU_CAPT_3R"
#define EventName_MCDU_CAPT_4R              "MCDU_CAPT_4R"
#define EventName_MCDU_CAPT_5R              "MCDU_CAPT_5R"
#define EventName_MCDU_CAPT_6R              "MCDU_CAPT_6R"

#define EventName_MCDU_CAPT_INIT            "MCDU_CAPT_INIT"
#define EventName_MCDU_CAPT_FPLN            "MCDU_CAPT_FPLN"
#define EventName_MCDU_CAPT_MENU            "MCDU_CAPT_MENU"

#define EventName_MCDU_CAPT_UP              "MCDU_CAPT_UP"
#define EventName_MCDU_CAPT_DOWN            "MCDU_CAPT_DOWN"
#define EventName_MCDU_CAPT_LEFT            "MCDU_CAPT_LEFT"
#define EventName_MCDU_CAPT_RIGHT           "MCDU_CAPT_RIGHT"

#define EventName_MCDU_CAPT_0               "MCDU_CAPT_0"
#define EventName_MCDU_CAPT_1               "MCDU_CAPT_1"
#define EventName_MCDU_CAPT_2               "MCDU_CAPT_2"
#define EventName_MCDU_CAPT_3               "MCDU_CAPT_3"
#define EventName_MCDU_CAPT_4               "MCDU_CAPT_4"
#define EventName_MCDU_CAPT_5               "MCDU_CAPT_5"
#define EventName_MCDU_CAPT_6               "MCDU_CAPT_6"
#define EventName_MCDU_CAPT_7               "MCDU_CAPT_7"
#define EventName_MCDU_CAPT_8               "MCDU_CAPT_8"
#define EventName_MCDU_CAPT_9               "MCDU_CAPT_9"

#define EventName_MCDU_CAPT_A               "MCDU_CAPT_A"
#define EventName_MCDU_CAPT_B               "MCDU_CAPT_B"
#define EventName_MCDU_CAPT_C               "MCDU_CAPT_C"
#define EventName_MCDU_CAPT_D               "MCDU_CAPT_D"
#define EventName_MCDU_CAPT_E               "MCDU_CAPT_E"
#define EventName_MCDU_CAPT_F               "MCDU_CAPT_F"
#define EventName_MCDU_CAPT_G               "MCDU_CAPT_G"
#define EventName_MCDU_CAPT_H               "MCDU_CAPT_H"
#define EventName_MCDU_CAPT_I               "MCDU_CAPT_I"
#define EventName_MCDU_CAPT_J               "MCDU_CAPT_J"
#define EventName_MCDU_CAPT_K               "MCDU_CAPT_K"
#define EventName_MCDU_CAPT_L               "MCDU_CAPT_L"
#define EventName_MCDU_CAPT_M               "MCDU_CAPT_M"
#define EventName_MCDU_CAPT_N               "MCDU_CAPT_N"
#define EventName_MCDU_CAPT_O               "MCDU_CAPT_O"
#define EventName_MCDU_CAPT_P               "MCDU_CAPT_P"
#define EventName_MCDU_CAPT_Q               "MCDU_CAPT_Q"
#define EventName_MCDU_CAPT_R               "MCDU_CAPT_R"
#define EventName_MCDU_CAPT_S               "MCDU_CAPT_S"
#define EventName_MCDU_CAPT_T               "MCDU_CAPT_T"
#define EventName_MCDU_CAPT_U               "MCDU_CAPT_U"
#define EventName_MCDU_CAPT_V               "MCDU_CAPT_V"
#define EventName_MCDU_CAPT_W               "MCDU_CAPT_W"
#define EventName_MCDU_CAPT_X               "MCDU_CAPT_X"
#define EventName_MCDU_CAPT_Y               "MCDU_CAPT_Y"
#define EventName_MCDU_CAPT_Z               "MCDU_CAPT_Z"

#define EventName_MCDU_CAPT_SPACE           "MCDU_CAPT_SPACE"
#define EventName_MCDU_CAPT_DELETE          "MCDU_CAPT_DELETE"
#define EventName_MCDU_CAPT_SLASH           "MCDU_CAPT_SLASH"
#define EventName_MCDU_CAPT_CLEAR           "MCDU_CAPT_CLEAR"

#define EventName_MCDU_FO_1L                "MCDU_FO_1L"
#define EventName_MCDU_FO_2L                "MCDU_FO_2L"
#define EventName_MCDU_FO_3L                "MCDU_FO_3L"
#define EventName_MCDU_FO_4L                "MCDU_FO_4L"
#define EventName_MCDU_FO_5L                "MCDU_FO_5L"
#define EventName_MCDU_FO_6L                "MCDU_FO_6L"
#define EventName_MCDU_FO_1R                "MCDU_FO_1R"
#define EventName_MCDU_FO_2R                "MCDU_FO_2R"
#define EventName_MCDU_FO_3R                "MCDU_FO_3R"
#define EventName_MCDU_FO_4R                "MCDU_FO_4R"
#define EventName_MCDU_FO_5R                "MCDU_FO_5R"
#define EventName_MCDU_FO_6R                "MCDU_FO_6R"

#define EventName_MCDU_FO_INIT              "MCDU_FO_INIT"
#define EventName_MCDU_FO_FPLN              "MCDU_FO_FPLN"
#define EventName_MCDU_FO_MENU              "MCDU_FO_MENU"

#define EventName_MCDU_FO_UP                "MCDU_FO_UP"
#define EventName_MCDU_FO_DOWN              "MCDU_FO_DOWN"
#define EventName_MCDU_FO_LEFT              "MCDU_FO_LEFT"
#define EventName_MCDU_FO_RIGHT             "MCDU_FO_RIGHT"

#define EventName_MCDU_FO_0                 "MCDU_FO_0"
#define EventName_MCDU_FO_1                 "MCDU_FO_1"
#define EventName_MCDU_FO_2                 "MCDU_FO_2"
#define EventName_MCDU_FO_3                 "MCDU_FO_3"
#define EventName_MCDU_FO_4                 "MCDU_FO_4"
#define EventName_MCDU_FO_5                 "MCDU_FO_5"
#define EventName_MCDU_FO_6                 "MCDU_FO_6"
#define EventName_MCDU_FO_7                 "MCDU_FO_7"
#define EventName_MCDU_FO_8                 "MCDU_FO_8"
#define EventName_MCDU_FO_9                 "MCDU_FO_9"

#define EventName_MCDU_FO_A                 "MCDU_FO_A"
#define EventName_MCDU_FO_B                 "MCDU_FO_B"
#define EventName_MCDU_FO_C                 "MCDU_FO_C"
#define EventName_MCDU_FO_D                 "MCDU_FO_D"
#define EventName_MCDU_FO_E                 "MCDU_FO_E"
#define EventName_MCDU_FO_F                 "MCDU_FO_F"
#define EventName_MCDU_FO_G                 "MCDU_FO_G"
#define EventName_MCDU_FO_H                 "MCDU_FO_H"
#define EventName_MCDU_FO_I                 "MCDU_FO_I"
#define EventName_MCDU_FO_J                 "MCDU_FO_J"
#define EventName_MCDU_FO_K                 "MCDU_FO_K"
#define EventName_MCDU_FO_L                 "MCDU_FO_L"
#define EventName_MCDU_FO_M                 "MCDU_FO_M"
#define EventName_MCDU_FO_N                 "MCDU_FO_N"
#define EventName_MCDU_FO_O                 "MCDU_FO_O"
#define EventName_MCDU_FO_P                 "MCDU_FO_P"
#define EventName_MCDU_FO_Q                 "MCDU_FO_Q"
#define EventName_MCDU_FO_R                 "MCDU_FO_R"
#define EventName_MCDU_FO_S                 "MCDU_FO_S"
#define EventName_MCDU_FO_T                 "MCDU_FO_T"
#define EventName_MCDU_FO_U                 "MCDU_FO_U"
#define EventName_MCDU_FO_V                 "MCDU_FO_V"
#define EventName_MCDU_FO_W                 "MCDU_FO_W"
#define EventName_MCDU_FO_X                 "MCDU_FO_X"
#define EventName_MCDU_FO_Y                 "MCDU_FO_Y"
#define EventName_MCDU_FO_Z                 "MCDU_FO_Z"

#define EventName_MCDU_FO_SPACE             "MCDU_FO_SPACE"
#define EventName_MCDU_FO_DELETE            "MCDU_FO_DELETE"
#define EventName_MCDU_FO_SLASH             "MCDU_FO_SLASH"
#define EventName_MCDU_FO_CLEAR             "MCDU_FO_CLEAR"

//-------------------------------------------------------------------------------------------------
// MCDU colors

#define A320_Color_Amber                    QColor(255, 128,   0)
#define A320_Color_Black                    QColor(  0,   0,   0)
#define A320_Color_Blue                     QColor(  0, 200, 255)
#define A320_Color_DarkGray                 QColor( 64,  64,  64)
#define A320_Color_Gray                     QColor(128, 128, 128)
#define A320_Color_Green                    QColor(  0, 255,   0)
#define A320_Color_Ground                   QColor( 96,  64,   0)
#define A320_Color_Purple                   QColor(255,   0, 128)
#define A320_Color_Red                      QColor(255,   0,   0)
#define A320_Color_Sky                      A320_Color_Blue
#define A320_Color_White                    QColor(255, 255, 255)
#define A320_Color_Yellow                   QColor(255, 255,   0)

#define A320_MCDU_FONT                      "Calibri"
