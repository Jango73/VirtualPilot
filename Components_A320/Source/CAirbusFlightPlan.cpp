
// qt-plus
#include "CLogger.h"

// Quick3D
#include "C3DScene.h"

// Application
#include "CAirbusFlightPlan.h"

using namespace Math;

//-------------------------------------------------------------------------------------------------

CAirbusFlightPlan::CAirbusFlightPlan()
    : m_dClimbVerticalSpeed_ms(2500.0 * FAC_FPM_TO_MS)
    , m_dDescentVerticalSpeed_ms(2500.0 * FAC_FPM_TO_MS)
    , m_dCruiseAltitude_m(33000.0 * FAC_FEET_TO_METERS)
    , m_dCruiseSpeed_ms(250.0 * FAC_KNOTS_TO_MS)
{
    LOG_DEBUG("CAirbusFlightPlan::CAirbusFlightPlan()");
}

//-------------------------------------------------------------------------------------------------

CAirbusFlightPlan::~CAirbusFlightPlan()
{
    LOG_DEBUG("CAirbusFlightPlan::~CAirbusFlightPlan()");
}

//-------------------------------------------------------------------------------------------------

void CAirbusFlightPlan::setCruiseAltitude_m(double dValue)
{
    m_dCruiseAltitude_m = dValue;
}

//-------------------------------------------------------------------------------------------------

void CAirbusFlightPlan::setCruiseSpeed_ms(double dValue)
{
    m_dCruiseSpeed_ms = dValue;
}

//-------------------------------------------------------------------------------------------------

void CAirbusFlightPlan::update(double dDeltaTime)
{
}

//-------------------------------------------------------------------------------------------------

void CAirbusFlightPlan::nextWaypoint()
{
    // Remove the first waypoint, the one we came from
    if (m_vWaypoints[WAYPOINT_TO].isGenerated() == false)
    {
        clearAllGeneratedWaypoints();

        if (m_vWaypoints.count() > 1)
        {
            m_vWaypoints.removeAt(0);
        }
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusFlightPlan::clearAllGeneratedWaypoints()
{
    for (int index = 0; index < m_vWaypoints.count(); index++)
    {
        if (m_vWaypoints[index].isGenerated())
        {
            m_vWaypoints.removeAt(index);
            index--;
        }
    }
}
