
#pragma once

// Application
#include "components_a320_global.h"

//-------------------------------------------------------------------------------------------------
// Facteurs de conversion

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

#define GETDATA_BOOL(d)         (data(d) != nullptr ? data(d)->data().toBool() : false)
#define GETDATA_INT(d)          (data(d) != nullptr ? data(d)->data().toInt() : 0)
#define GETDATA_DOUBLE(d)       (data(d) != nullptr ? data(d)->data().toDouble() : 0.0)
#define GETDATA_STRING(d)       (data(d) != nullptr ? data(d)->data().toString() : "")
#define GETDATA_POINTER(d,t)    (data(d) != nullptr ? (t*) data(d)->data().toULongLong() : nullptr)

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
    adFCU_AutoPilot1_Engaged,
    adFCU_AutoPilot2_Engaged,
    adFCU_AutoThrust_Engaged,
    adFCU_VerticalSpeed_fs,
    adFCU_Altitude_f,
    adFCU_VelocityType_idx,
    adFCU_Velocity_kts,
    adFCU_Velocity_mach,
    adFCU_HeadingType_idx,
    adFCU_Heading_deg
};

//-------------------------------------------------------------------------------------------------
// Flight laws

enum EFlightLaw
{
    flNormal
};

//-------------------------------------------------------------------------------------------------
// Flight phases

enum EFlightPhase
{
    fpPark,
    fpTaxi,
    fpTakeoff,
    fpClimb,
    fpCruise,
    fpDescent,
    fpApproach,
    fpLand,
    fpGoAround,
    fpTaxiToGate
};

//-------------------------------------------------------------------------------------------------
// Lateral navigation modes

enum EAirbusLateralMode
{
    almNone,
    almHeading,
    almNav
};

//-------------------------------------------------------------------------------------------------
// Vertical navigation modes

enum EAirbusVerticalMode
{
    avmNone,
    avmVerticalSpeedHold,
    avmAltitudeHold,
    avmNav,
    avmOpenClimb,
    avmOpenDescent,
    avmClimb,
    avmDescent
};

//-------------------------------------------------------------------------------------------------

enum EMCDUDataSet
{
    mdsNone,
    mdsCompanyRoute,
    mdsICAOFromTo
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
