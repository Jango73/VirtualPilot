
// qt-plus
#include "CLogger.h"

// Quick3D
#include "CConsoleBoard.h"
#include "C3DScene.h"
#include "CAircraft.h"

// Application
#include "CAirbusADIRU.h"

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusADIRU::instantiator(C3DScene* pScene)
{
    return new CAirbusADIRU(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusADIRU::CAirbusADIRU(C3DScene* pScene)
    : CAirbusFlightComputer(pScene)
    , m_dPreviousIndicatedAirSpeed_ms(0.0)
{
}

//-------------------------------------------------------------------------------------------------

CAirbusADIRU::~CAirbusADIRU()
{
}

//-------------------------------------------------------------------------------------------------

void CAirbusADIRU::update(double dDeltaTime)
{
    CAirbusFlightComputer::update(dDeltaTime);
}

//-------------------------------------------------------------------------------------------------

void CAirbusADIRU::work(double dDeltaTime)
{
    CAirbusFlightComputer::work(dDeltaTime);

    QSP<CAircraft> pAircraft = QSP_CAST(CAircraft, root());

    if (pAircraft != nullptr)
    {
        // Compute pitch
        double dPitch_deg = pAircraft->pitch_deg();
        pushData(CAirbusData(m_sName, adInertial_Pitch_deg, dPitch_deg));

        // Compute roll
        double dRoll_deg = pAircraft->roll_deg();
        pushData(CAirbusData(m_sName, adInertial_Roll_deg, dRoll_deg));

        // Compute true heading
        double dTrueHeading_deg = pAircraft->trueHeading_deg();
        pushData(CAirbusData(m_sName, adGeoLoc_TrueHeading_deg, dTrueHeading_deg));

        // Compute track
        double dTrueTrack_deg = pAircraft->trueTrack_deg();
        pushData(CAirbusData(m_sName, adGeoLoc_TrueTrack_deg, dTrueTrack_deg));

        CVector3 vAngularVelocity_rs = pAircraft->angularVelocity_rs();

        // Compute roll velocity
        double dInertial_RollVelocity_ds = Math::Angles::toDeg(vAngularVelocity_rs.Z);
        pushData(CAirbusData(m_sName, adInertial_RollVelocity_ds, dInertial_RollVelocity_ds));

        // Compute pitch velocity
        double dInertial_PitchVelocity_ds = Math::Angles::toDeg(vAngularVelocity_rs.X);
        pushData(CAirbusData(m_sName, adInertial_PitchVelocity_ds, dInertial_PitchVelocity_ds));

        // Compute true air speed
        double dTrueAirSpeed_ms = pAircraft->trueAirSpeed_ms();
        pushData(CAirbusData(m_sName, adAir_TrueAirspeed_ms, dTrueAirSpeed_ms));

        // Compute indicated air speed
        double dIndicatedAirSpeed_ms = pAircraft->indicatedAirSpeed_ms();
        pushData(CAirbusData(m_sName, adAir_IndicatedAirspeed_ms, dIndicatedAirSpeed_ms));

        double dIndicatedAccel_ms = (dIndicatedAirSpeed_ms - m_dPreviousIndicatedAirSpeed_ms) / dDeltaTime;
        pushData(CAirbusData(m_sName, adAir_IndicatedAcceleration_ms, dIndicatedAccel_ms));

        // Compute VMax
        pushData(CAirbusData(m_sName, adAir_IndicatedAirspeedVMax_ms, 140.0));

        // Compute Mach
        double dMach = pAircraft->mach();
        pushData(CAirbusData(m_sName, adAir_Mach, dMach));

        // Compute ground speed
        double dGroundSpeed_ms = pAircraft->groundSpeed_ms();
        pushData(CAirbusData(m_sName, adGeoLoc_GroundSpeed_ms, dGroundSpeed_ms));

        // Compute vertical speed
        double dVerticalSpeed_ms = pAircraft->verticalSpeed_ms();
        pushData(CAirbusData(m_sName, adAir_VerticalSpeed_ms, dVerticalSpeed_ms));

        // Compute latitude
        double dLatitude_deg = Angles::toDeg(pAircraft->geoloc().Latitude);
        pushData(CAirbusData(m_sName, adGeoLoc_Latitude_deg, dLatitude_deg));

        // Compute longitude
        double dLongitude_deg = Angles::toDeg(pAircraft->geoloc().Longitude);
        pushData(CAirbusData(m_sName, adGeoLoc_Longitude_deg, dLongitude_deg));

        // Compute altitude
        double dAltitude_m = pAircraft->altitude_m();
        pushData(CAirbusData(m_sName, adAir_Altitude_m, dAltitude_m));
        pushData(CAirbusData(m_sName, adGeoLoc_Altitude_m, dAltitude_m));

        // Compute radar altitude
        double dAltitudeAGL_m = pAircraft->altitudeAGL_m();
        pushData(CAirbusData(m_sName, adRadar_AltitudeAGL_m, dAltitudeAGL_m));

        // Log some values
        LOG_VALUE(QString("%1 (GS/TRK/MCH)").arg(m_sName),
                  QString("%1 / %2 / %3")
                  .arg(QString::number(dGroundSpeed_ms, 'f', 2))
                  .arg(QString::number(dTrueHeading_deg, 'f', 2))
                  .arg(QString::number(dMach, 'f', 2))
                  );

        m_dPreviousIndicatedAirSpeed_ms = dIndicatedAirSpeed_ms;
    }
}
