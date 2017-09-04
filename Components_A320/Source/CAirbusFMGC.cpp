
// qt-plus
#include "CLogger.h"

// Quick3D
#include "CConsoleBoard.h"
#include "C3DScene.h"

// Application
#include "CAirbusFMGC.h"

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusFMGC::instantiator(C3DScene* pScene)
{
    return new CAirbusFMGC(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusFMGC::CAirbusFMGC(C3DScene* pScene)
    : CAirbusFlightComputer(pScene)
    , m_eFlightPhase(fpTaxi)
    , m_eLateralMode(almNone)
    , m_eVerticalMode(avmNone)
    , m_pidVerticalSpeed(5.0, 0.0, 0.1)
    , m_pidAcceleration(0.5, 0.0, 0.001)
    , m_pidDeceleration(0.02, 0.0, 0.001)
    , m_dDeltaTime(0.0)
    , m_dCommandedHeading_deg(0.0)
    , m_dCommandedVerticalSpeed_ms(0.0)
    , m_dCommandedAltitude_m(0.0)
    , m_dCommandedRoll_deg(0.0)
    , m_dCommandedRollVelocity_ds(0.0)
    , m_dCommandedVelocity_ms(0.0)
    , m_dCommandedAcceleration_ms(0.0)
{
    LOG_DEBUG("CAirbusFMGC::CAirbusFMGC()");

    loadFlightPlan();

    m_tLastUpdate = QDateTime::currentDateTime();
}

//-------------------------------------------------------------------------------------------------

CAirbusFMGC::~CAirbusFMGC()
{
    LOG_DEBUG("CAirbusFMGC::~CAirbusFMGC()");
}

//-------------------------------------------------------------------------------------------------

void CAirbusFMGC::loadFlightPlan()
{
    m_tFlightPlan.waypoints() << CWaypoint(wtAirport, "WP1", CGeoloc(19.2, 10.8, 0.0), 0.0);

    m_tFlightPlan.waypoints() << CWaypoint(wtFix, "WP2", CGeoloc(19.4, 10.8, 0.0), 0.0);
    m_tFlightPlan.lastWaypoint().setMinimumAltitude_m(3000.0 * FAC_FEET_TO_METERS);

    m_tFlightPlan.waypoints() << CWaypoint(wtFix, "WP3", CGeoloc(19.5, 10.9, 0.0), 0.0);
    m_tFlightPlan.lastWaypoint().setMinimumAltitude_m(3000.0 * FAC_FEET_TO_METERS);

    m_tFlightPlan.waypoints() << CWaypoint(wtFix, "WP4", CGeoloc(19.5, 11.0, 0.0), 0.0);
    m_tFlightPlan.waypoints() << CWaypoint(wtFix, "WP5", CGeoloc(19.6, 11.2, 0.0), 0.0);

    m_tFlightPlan.waypoints() << CWaypoint(wtFix, "WP6", CGeoloc(19.6, 12.0, 0.0), 0.0);
    m_tFlightPlan.lastWaypoint().setSelectedAltitude_m(2500.0 * FAC_FEET_TO_METERS);

    m_tFlightPlan.waypoints() << CWaypoint(wtRunway, "WP7", CGeoloc(19.6, 12.1, 0.0), 0.0);
}

//-------------------------------------------------------------------------------------------------

void CAirbusFMGC::update(double dDeltaTime)
{
    CAirbusFlightComputer::update(dDeltaTime);
}

//-------------------------------------------------------------------------------------------------

void CAirbusFMGC::work(double dDeltaTime)
{
    CAirbusFlightComputer::work(dDeltaTime);

    if (m_iUnitIndex == 0)
    {
        m_dDeltaTime = dDeltaTime;

        computeFlightPhase(dDeltaTime);

        // Flight Management
        work_FM(dDeltaTime);

        // Flight Guidance
        work_FG(dDeltaTime);
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusFMGC::work_FM(double dDeltaTime)
{
    // Data processing from MCDU
    work_FM_ProcessMCDUData(dDeltaTime);

    // Predictions computing
    work_FM_doPredictions(dDeltaTime);

    // Send flight plan
    pushData(CAirbusData(m_sName, adFG_FlightPlan_ptr, (quint64) &m_tFlightPlan, false));
    pushData(CAirbusData(m_sName, adFM_CompanyRoute, m_tFlightPlan.companyRoute(), false));
    pushData(CAirbusData(m_sName, adFM_FlightNumber, m_tFlightPlan.flightNumber(), false));
    pushData(CAirbusData(m_sName, adFM_ICAOFrom, m_tFlightPlan.ICAOFrom(), false));
    pushData(CAirbusData(m_sName, adFM_ICAOTo, m_tFlightPlan.ICAOTo(), false));
}

//-------------------------------------------------------------------------------------------------

void CAirbusFMGC::work_FM_ProcessMCDUData(double dDeltaTime)
{
    Q_UNUSED(dDeltaTime);

    EMCDUDataSet eMCDU_DataSetName = (EMCDUDataSet) GETDATA_INT(adMCDU_DataSetName);

    if (eMCDU_DataSetName != mdsNone)
    {
        removeData(adMCDU_DataSetName);

        switch (eMCDU_DataSetName)
        {
            case mdsCompanyRoute:
                m_tFlightPlan.setCompanyRoute(GETDATA_STRING(adMCDU_DataSetValue));
                break;

            case mdsICAOFromTo:
                QStringList lICAO = GETDATA_STRING(adMCDU_DataSetValue).split("/");

                if (lICAO.count() == 2)
                {
                    m_tFlightPlan.setICAOFrom(lICAO[0]);
                    m_tFlightPlan.setICAOTo(lICAO[1]);
                }
                break;
        }
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusFMGC::work_FM_doPredictions(double dDeltaTime)
{
    Q_UNUSED(dDeltaTime);

    // Compute very 2 seconds
    if (m_tLastUpdate.secsTo(QDateTime::currentDateTime()) > 2)
    {
        m_tLastUpdate = QDateTime::currentDateTime();

        // Get flight data
        double dAircraftAltitude_m = GETDATA_DOUBLE(adAir_Altitude_m);
        double dAircraftVerticalSpeed_ms = GETDATA_DOUBLE(adAir_VerticalSpeed_ms);

        // Clear generated data
        m_tFlightPlan.clearAllGeneratedWaypoints();

        if (m_tFlightPlan.waypoints().count() > 1)
        {
            // Set markers
            bool bClimbDone = false;
            bool bDescentDone = false;

            if (m_eFlightPhase > fpClimb)
            {
                bClimbDone = true;
            }

            if (m_eFlightPhase > fpDescent)
            {
                bDescentDone = true;
            }

            // Set computed altitude for each waypoint
            for (int index = 0; index < m_tFlightPlan.waypoints().count(); index++)
            {
                double dComputedAltitude = 0.0;

                if (index == 0)
                {
                    dComputedAltitude = dAircraftAltitude_m;
                }
                else
                {
                    if (m_tFlightPlan.waypoints()[index].selectedAltitude_m() != 0.0)
                    {
                        // Check if selected altitude passes constraints
                        if (m_tFlightPlan.waypoints()[index].maximumAltitude_m() != 0.0)
                        {
                            if (m_tFlightPlan.waypoints()[index].selectedAltitude_m() <= m_tFlightPlan.waypoints()[index].maximumAltitude_m())
                            {
                                dComputedAltitude = m_tFlightPlan.waypoints()[index].selectedAltitude_m();
                            }
                        }
                        else if (m_tFlightPlan.waypoints()[index].minimumAltitude_m() != 0.0)
                        {
                            if (m_tFlightPlan.waypoints()[index].selectedAltitude_m() >= m_tFlightPlan.waypoints()[index].minimumAltitude_m())
                            {
                                dComputedAltitude = m_tFlightPlan.waypoints()[index].selectedAltitude_m();
                            }
                        }
                        else
                        {
                            dComputedAltitude = m_tFlightPlan.waypoints()[index].selectedAltitude_m();
                        }
                    }
                    else
                    {
                        dComputedAltitude = m_tFlightPlan.cruiseAltitude_m();
                    }

                    m_tFlightPlan.waypoints()[index].setComputedAltitude_m(dComputedAltitude);
                }
            }

            // Compute effective altitude at each waypoint
            for (int index = 0; index < m_tFlightPlan.waypoints().count(); index++)
            {
                if (bClimbDone == false)
                {
                }
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusFMGC::work_FG(double dDeltaTime)
{
    bool bFCU_Lateral_Managed = GETDATA_BOOL(adFCU_Lateral_Managed);
    bool bFCU_Vertical_Managed = GETDATA_BOOL(adFCU_Vertical_Managed);
    double dFCU_Altitude_f = GETDATA_DOUBLE(adFCU_Altitude_f);
    double dFCU_Heading_deg = GETDATA_DOUBLE(adFCU_Heading_deg);
    double dGeoLoc_Latitude_deg = GETDATA_DOUBLE(adGeoLoc_Latitude_deg);
    double dGeoLoc_Longitude_deg = GETDATA_DOUBLE(adGeoLoc_Longitude_deg);
    double dGeoLoc_TrueHeading_deg = GETDATA_DOUBLE(adGeoLoc_TrueHeading_deg);
    double dGeoLoc_TrueTrack_deg = GETDATA_DOUBLE(adGeoLoc_TrueTrack_deg);
    double dGeoLoc_GroundSpeed_ms = GETDATA_DOUBLE(adGeoLoc_GroundSpeed_ms);
    double dAir_Altitude_m = GETDATA_DOUBLE(adAir_Altitude_m);
    double dAircraftVerticalSpeed_ms = GETDATA_DOUBLE(adAir_VerticalSpeed_ms);
    double dAir_IndicatedAirspeed_ms = GETDATA_DOUBLE(adAir_IndicatedAirspeed_ms);
    double dAir_IndicatedAcceleration_ms = GETDATA_DOUBLE(adAir_IndicatedAcceleration_ms);
    double dInertial_Roll_deg = GETDATA_DOUBLE(adInertial_Roll_deg);
    double dInertial_Pitch_deg = GETDATA_DOUBLE(adInertial_Pitch_deg);

    CGeoloc gGeoloc(Angles::toRad(dGeoLoc_Latitude_deg), Angles::toRad(dGeoLoc_Longitude_deg), 0.0);

    // Compute auto heading

    if (bFCU_Lateral_Managed && m_tFlightPlan.waypoints().count() > 1)
    {
        m_eLateralMode = almNav;

        // Get two points of current segment
        CGeoloc gSegmentStart = m_tFlightPlan.waypoints()[WAYPOINT_TO - 1].geoloc();
        CGeoloc gSegmentEnd = m_tFlightPlan.waypoints()[WAYPOINT_TO + 0].geoloc();

        CVector3 vSegmentStart = gSegmentStart.toVector3(gGeoloc);
        CVector3 vSegmentEnd = gSegmentEnd.toVector3(gGeoloc);

        // Compute distance to waypoint
        double dDistanceToSegmentEnd = vSegmentEnd.magnitude();

        // Compute angle between start point and end point
        double dSegmentStartSegmentEndAngle_rad = (vSegmentEnd - vSegmentStart).eulerYAngle();
        double dAircraftSegmentEndAngle_rad = vSegmentEnd.eulerYAngle();

        // Create a rotation matrix using the inverse angle between start and end points
        CMatrix4 mSegmentAngle = CMatrix4::makeRotation(CVector3(0.0, -dSegmentStartSegmentEndAngle_rad, 0.0));

        // Rotate the two segment points
        vSegmentStart = mSegmentAngle * vSegmentStart;
        vSegmentEnd = mSegmentAngle * vSegmentEnd;

        // Compute deviation
        double dDeviation_rad = vSegmentEnd.eulerYAngle();
        double dHeading_rad = dAircraftSegmentEndAngle_rad + dDeviation_rad * 2.0;

        m_dCommandedHeading_deg = Angles::toDeg(dHeading_rad);

        // Check if aircraft has reached waypoint
        if (dDistanceToSegmentEnd < dGeoLoc_GroundSpeed_ms * 20.0)
        {
            m_tFlightPlan.nextWaypoint();
        }
    }
    else
    {
        m_eLateralMode = almHeading;
        m_dCommandedHeading_deg = dFCU_Heading_deg;
    }

    // Compute heading commands

    m_dCommandedRoll_deg = Math::Angles::angleDifferenceDegree(m_dCommandedHeading_deg, dGeoLoc_TrueHeading_deg);
    m_dCommandedRoll_deg = m_dCommandedRoll_deg * -2.0;
    m_dCommandedRoll_deg = Math::Angles::clipDouble(m_dCommandedRoll_deg, -30.0, 30.0);

    m_dCommandedRollVelocity_ds = m_dCommandedRoll_deg - dInertial_Roll_deg;
    m_dCommandedRollVelocity_ds = Math::Angles::clipDouble(m_dCommandedRollVelocity_ds, -10.0, 10.0);

    // Compute auto altitude

    if (
            bFCU_Vertical_Managed &&
            m_tFlightPlan.waypoints().count() > 1 &&
            m_tFlightPlan.waypoints()[WAYPOINT_TO].computedAltitude_m() != 0.0
            )
    {
        m_eVerticalMode = avmClimb;
        m_dCommandedAltitude_m = m_tFlightPlan.waypoints()[WAYPOINT_TO].computedAltitude_m();
    }
    else
    {
        m_eVerticalMode = avmAltitudeHold;
        m_dCommandedAltitude_m = dFCU_Altitude_f;
    }

    // Compute altitude commands

    m_dCommandedVerticalSpeed_ms = (m_dCommandedAltitude_m - dAir_Altitude_m) * 0.25;
    m_dCommandedVerticalSpeed_ms = Math::Angles::clipDouble(m_dCommandedVerticalSpeed_ms, -8.0, 8.0);

    m_pidVerticalSpeed.setSetPoint(m_dCommandedVerticalSpeed_ms);
    m_pidVerticalSpeed.update(dAircraftVerticalSpeed_ms, m_dDeltaTime * 1000.0);

    m_dCommandedPitch_deg = -m_pidVerticalSpeed.output();
    m_dCommandedPitch_deg = Math::Angles::clipDouble(m_dCommandedPitch_deg, -20.0, 10.0);

    m_dCommandedPitchVelocity_ds = (m_dCommandedPitch_deg - dInertial_Pitch_deg) * 0.5;
    m_dCommandedPitchVelocity_ds = Math::Angles::clipDouble(m_dCommandedPitchVelocity_ds, -3.0, 3.0);

    // Compute thrust command

    m_dCommandedVelocity_ms = 250.0 * FAC_KNOTS_TO_MS;

    m_dCommandedAcceleration_ms = (m_dCommandedVelocity_ms - dAir_IndicatedAirspeed_ms) * 0.5;
    m_dCommandedAcceleration_ms = Math::Angles::clipDouble(m_dCommandedAcceleration_ms, -2.0, 2.0);

    m_pidAcceleration.setSetPoint(m_dCommandedAcceleration_ms);
    m_pidAcceleration.update(dAir_IndicatedAcceleration_ms, m_dDeltaTime * 1000.0);

    m_pidDeceleration.setSetPoint(m_dCommandedAcceleration_ms);
    m_pidDeceleration.update(dAir_IndicatedAcceleration_ms, m_dDeltaTime * 1000.0);

    if (m_dCommandedAcceleration_ms > dAir_IndicatedAcceleration_ms)
    {
        m_dCommandedThrust_norm = m_pidAcceleration.output();
    }
    else
    {
        m_dCommandedThrust_norm = m_pidDeceleration.output();
    }

    // Send data

    pushData(CAirbusData(m_sName, adFG_FlightPhase_fp, m_eFlightPhase));
    pushData(CAirbusData(m_sName, adFG_LateralMode_alm, m_eLateralMode));
    pushData(CAirbusData(m_sName, adFG_VerticalMode_avm, m_eVerticalMode));
    pushData(CAirbusData(m_sName, adFG_CommandedRollVelocity_ds, m_dCommandedRollVelocity_ds));
    pushData(CAirbusData(m_sName, adFG_CommandedPitchVelocity_ds, m_dCommandedPitchVelocity_ds));
    pushData(CAirbusData(m_sName, adFG_CommandedThrust_norm, m_dCommandedThrust_norm));

    // Debug information

    LOG_VALUE(QString("%1 HDG / ROLL / ROLL VEL").arg(m_sName),
              QString("%1 / %2 / %3")
              .arg(QString::number(m_dCommandedHeading_deg, 'f', 2))
              .arg(QString::number(m_dCommandedRoll_deg, 'f', 2))
              .arg(QString::number(m_dCommandedRollVelocity_ds, 'f', 2))
              );

    LOG_VALUE(QString("%1 VS / PITCH / PITCH VEL").arg(m_sName),
              QString("%1 / %2 / %3")
              .arg(QString::number(m_dCommandedVerticalSpeed_ms, 'f', 2))
              .arg(QString::number(m_dCommandedPitch_deg, 'f', 2))
              .arg(QString::number(m_dCommandedPitchVelocity_ds, 'f', 2))
              );

    LOG_VALUE(QString("%1 VEL / ACCEL / THT").arg(m_sName),
              QString("%1 / %2 / %3")
              .arg(QString::number(m_dCommandedVelocity_ms, 'f', 2))
              .arg(QString::number(m_dCommandedAcceleration_ms, 'f', 2))
              .arg(QString::number(m_dCommandedThrust_norm, 'f', 2))
              );
}

//-------------------------------------------------------------------------------------------------

void CAirbusFMGC::computeFlightPhase(double dDeltaTime)
{
    double dAir_Altitude_m = GETDATA_DOUBLE(adAir_Altitude_m);
    double dAir_VerticalSpeed_ms = GETDATA_DOUBLE(adAir_VerticalSpeed_ms);
    double dGeoLoc_GroundSpeed_ms = GETDATA_DOUBLE(adGeoLoc_GroundSpeed_ms);
    double dRadar_AltitudeAGL_m = GETDATA_DOUBLE(adRadar_AltitudeAGL_m);
    double dThrottle_1_norm = GETDATA_DOUBLE(adThrottle_1_norm);
    double dThrottle_2_norm = GETDATA_DOUBLE(adThrottle_2_norm);

    switch (m_eFlightPhase)
    {
        case fpPark:
            break;

        case fpTaxi:
            if (dThrottle_1_norm > FP_TAXI_THRUST_THRESHOLD || dThrottle_2_norm > FP_TAXI_THRUST_THRESHOLD)
            {
                m_eFlightPhase = fpTakeoff;
            }
            break;

        case fpTakeoff:
            if (dRadar_AltitudeAGL_m > FP_TAKEOFF_ALTITUDE_AGL_THRESHOLD)
            {
                m_eFlightPhase = fpClimb;
            }
            else if (dThrottle_1_norm < FP_TAXI_THRUST_THRESHOLD)
            {
                m_eFlightPhase = fpLand;
            }
            break;

        case fpClimb:
            if (m_tFlightPlan.cruiseAltitude_m() != 0.0)
            {
                double dCurrentAndCruiseAltDiff = fabs(m_tFlightPlan.cruiseAltitude_m() - dAir_Altitude_m);

                if (dCurrentAndCruiseAltDiff < FP_CLIMB_ALTITUDE_THRESHOLD)
                {
                    m_eFlightPhase = fpCruise;
                }
            }
            else if (dAir_VerticalSpeed_ms < -FP_CRUISE_VERTSPEED_THRESHOLD)
            {
                m_eFlightPhase = fpDescent;
            }
            break;

        case fpCruise:
            if (dAir_VerticalSpeed_ms < -FP_CRUISE_VERTSPEED_THRESHOLD)
            {
                m_eFlightPhase = fpDescent;
            }
            else if (dRadar_AltitudeAGL_m < FP_CRUISE_ALTITUDE_AGL_THRESHOLD)
            {
                m_eFlightPhase = fpDescent;
            }
            break;

        case fpDescent:
            if (dRadar_AltitudeAGL_m < FP_DESCENT_ALTITUDE_AGL_THRESHOLD)
            {
                m_eFlightPhase = fpApproach;
            }
            break;

        case fpApproach:
            if (dRadar_AltitudeAGL_m < FP_TAKEOFF_ALTITUDE_AGL_THRESHOLD)
            {
                m_eFlightPhase = fpLand;
            }
            break;

        case fpLand:
            if (dGeoLoc_GroundSpeed_ms < FP_LAND_GROUNDSPEED_THRESHOLD)
            {
                m_eFlightPhase = fpTaxi;
            }
            break;
    }
}
