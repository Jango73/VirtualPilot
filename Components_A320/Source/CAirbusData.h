
#pragma once

// Application
#include "components_a320_global.h"

//-------------------------------------------------------------------------------------------------
// Conversion factors

// Meters <-> Feet
#define FAC_METERS_TO_FEET	3.280840
#define FAC_FEET_TO_METERS	(1.0 / FAC_METERS_TO_FEET)

// Meters per second <-> Kilometers per hour
#define FAC_MS_TO_KMH		3.600000
#define FAC_KMH_TO_MS		(1.0 / FAC_MS_TO_KMH)

// Meters per second <-> Knots
#define FAC_MS_TO_KNOTS		1.943840
#define FAC_KNOTS_TO_MS		(1.0 / FAC_MS_TO_KNOTS)

// Meters per second <-> Feet per minute
#define FAC_MS_TO_FPM		(FAC_METERS_TO_FEET * 60.0)
#define FAC_FPM_TO_MS		(1.0 / FAC_MS_TO_FPM)

// Kilometers per hour <-> Knots
#define FAC_KMH_TO_KNOTS	0.539957
#define FAC_KNOTS_TO_KMH	(1.0 / FAC_KMH_TO_KNOTS)

// Meters <-> Nautical miles
#define FAC_M_TO_NM			0.000539957
#define FAC_NM_TO_M			(1.0 / FAC_M_TO_NM)

// Kilometers <-> Nautical miles
#define FAC_KM_TO_NM		0.539957
#define FAC_NM_TO_KM		(1.0 / FAC_KM_TO_NM)

//-------------------------------------------------------------------------------------------------

enum EAirbusData
{
    adNone,

    // Data coming from static ports
    adStatic_Pressure_kgm2,

    // Data coming from ADIRU
    adAir_Altitude_m,
    adAir_AngleOfAttack_rad,
    adAir_TrueAirspeed_ms,
    adAir_IndicatedAirspeed_ms,
    adAir_IndicatedAcceleration_ms,
    adAir_IndicatedAirspeedVMax_ms,
    adAir_Mach,
    adAir_VerticalSpeed_ms,
    adInertial_Pitch_deg,
    adInertial_Roll_deg,
    adInertial_PitchVelocity_ds,
    adInertial_RollVelocity_ds,
    adGeoLoc_Latitude_deg,
    adGeoLoc_Longitude_deg,
    adGeoLoc_Altitude_m,
    adGeoLoc_GroundSpeed_ms,
    adGeoLoc_TrueHeading_deg,
    adGeoLoc_TrueTrack_deg,
    adRadar_AltitudeAGL_m,

    // Data coming from gear sensor
    adGear_OnGround_bool,

    // Data coming from ?
    adFuel_TotalFuel_l,

    // Data coming from side sticks and throttle
    adStick_CAPT_x,
    adStick_CAPT_y,
    adStick_FO_x,
    adStick_FO_y,
    adRudder_CAPT,
    adRudder_FO,
    adThrottle_1_norm,
    adThrottle_2_norm,

    // Data coming from electrical components
    adELEC_Gen1_Power_v,
    adELEC_Gen1_Freq_hz,
    adELEC_Gen2_Power_v,
    adELEC_Gen2_Freq_hz,
    adELEC_GenAPU_Power_v,
    adELEC_GenAPU_Freq_hz,
    adELEC_ACBus1_Power_v,
    adELEC_ACBus2_Power_v,
    adELEC_Tr1_Power_v,
    adELEC_Tr1_Load_a,
    adELEC_Tr2_Power_v,
    adELEC_Tr2_Load_a,
    adELEC_EssTr_Power_v,
    adELEC_EssTr_Load_a,
    adELEC_DCBus1_Power_v,
    adELEC_DCBus2_Power_v,
    adELEC_DCBatBus_Power_v,
    adELEC_DCEssBus_Power_v,
    adELEC_ACEssBus_Power_v,

    adELEC_Cont_Gen1_bool,
    adELEC_Cont_Gen2_bool,
    adELEC_Cont_GenAPU_bool,
    adELEC_Cont_ACTie1_bool,
    adELEC_Cont_ACTie2_bool,
    adELEC_Cont_Tr1_bool,
    adELEC_Cont_Tr2_bool,
    adELEC_Cont_DCTie1_bool,
    adELEC_Cont_DCTie2_bool,
    adELEC_Cont_EssTr_bool,
    adELEC_Cont_ACEssFeed_1_bool,
    adELEC_Cont_ACEssFeed_2_bool,

    // Data coming from FADEC
    adFADEC_Engine1_N1_norm,
    adFADEC_Engine1_N2_norm,
    adFADEC_Engine2_N1_norm,
    adFADEC_Engine2_N2_norm,

    // Data coming from FMGS
    adFG_FlightPhase_fp,
    adFG_LateralMode_alm,
    adFG_VerticalMode_avm,
    adFG_CommandedRollVelocity_ds,
    adFG_CommandedPitchVelocity_ds,
    adFG_CommandedThrust_norm,
    adFG_FlightPlan_ptr,

    adFM_CompanyRoute,
    adFM_FlightNumber,
    adFM_ICAOFrom,
    adFM_ICAOTo,

    // Data coming from MCDU
    adMCDU_DataSetName,
    adMCDU_DataSetValue,

    // Data coming from FCU
    adFCU_AutoPilot1_Engaged_bool,
    adFCU_AutoPilot2_Engaged_bool,
    adFCU_AutoThrust_Engaged_bool,
    adFCU_Lateral_Managed_bool,
    adFCU_Vertical_Managed_bool,
    adFCU_VerticalSpeed_fs,
    adFCU_Altitude_f,
    adFCU_VelocityType_idx,
    adFCU_Velocity_kts,
    adFCU_Velocity_mach,
    adFCU_HeadingType_idx,
    adFCU_Heading_deg,

    // Data coming from electrical panel
    adELEC_Generator1_Online_bool,
    adELEC_Generator2_Online_bool,

    // Data coming from SD controls
    adSD_Page_idx
};

//-------------------------------------------------------------------------------------------------
// Flight laws

enum EFlightLaw
{
    flNormal,
    flAlternate1,
    flAlternate2,
    flDirect,
    flMechanical
};

//-------------------------------------------------------------------------------------------------
// Flight phases

enum EAirbusFlightPhase
{
    fpNone,
    fpPark,
    fpTaxi,
    fpTakeoff,
    fpClimb,
    fpCruise,
    fpDescent,
    fpApproach,
    fpLand,
    fpGoAround
};

//-------------------------------------------------------------------------------------------------
// Lateral navigation modes

enum EAirbusLateralMode
{
    almNone,
    almHeading,
    almNav,
    almAppNav,
    almLoc,
    almRunway,
    almRunwayTrack,
    almGoAroundTrack,
    almRollOut
};

//-------------------------------------------------------------------------------------------------
// Vertical navigation modes

enum EAirbusVerticalMode
{
    avmNone,
    avmOpenClimb,
    avmOpenDescent,
    avmVerticalSpeedHold,
    avmAltitudeHold,
    avmClimb,
    avmDescent,
    avmAltitudeConstraint,
    avmAltitudeCruise,
    avmGlideSlope,
    avmFinal,
    avmFinalApproach,
    avmFlare
};

//-------------------------------------------------------------------------------------------------
// Data setting from MCDU to FMGC

enum EMCDUDataSet
{
    mdsNone,
    mdsCompanyRoute,
    mdsICAOFromTo
};

//-------------------------------------------------------------------------------------------------
// System display pages

enum ESDPage
{
    sdpElectrical,
    sdpHydraulic
};

//-------------------------------------------------------------------------------------------------

class CAirbusData
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    CAirbusData();

    //!
    CAirbusData(const QString& source, EAirbusData eID, QVariant vData, bool bContinuous = true);

    //!
    virtual ~CAirbusData();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //!
    void setSource(QString sText) { m_sSource = sText; }

    //!
    void setID(EAirbusData eID) { m_eID = eID; }

    //!
    void setUpdateTime(QDateTime dValue) { m_dUpdateTime = dValue; }

    //!
    void setData(QVariant vData) { m_vData = vData; }

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //!
    QString source() const { return m_sSource; }

    //!
    EAirbusData ID() const { return m_eID; }

    //!
    QVariant data() const { return m_vData; }

    //!
    bool valid() const;

    //-------------------------------------------------------------------------------------------------
    // Inherited methods
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    QString             m_sSource;
    EAirbusData         m_eID;
    QDateTime           m_dUpdateTime;
    QVariant            m_vData;
    bool                m_bContinuous;
};
