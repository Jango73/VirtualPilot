
#pragma once

// Quick3D
#include "CWaypoint.h"

// Application
#include "components_a320_global.h"
#include "CAirbusData.h"
#include "Constants.h"

//-------------------------------------------------------------------------------------------------

#define WAYPOINT_TO 1

class COMPONENTS_A320_EXPORT CAirbusFlightPlan
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    CAirbusFlightPlan();

    //!
    virtual ~CAirbusFlightPlan();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //!
    void setCruiseAltitude_m(double dValue);

    //!
    void setCruiseSpeed_ms(double dValue);

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //!
    QVector<CWaypoint>& waypoints() { return m_vWaypoints; }

    //!
    CWaypoint& lastWaypoint() { return m_vWaypoints.last(); }

    //!
    double climbVerticalSpeed_ms() { return m_dClimbVerticalSpeed_ms; }

    //!
    double descentVerticalSpeed_ms() { return m_dDescentVerticalSpeed_ms; }

    //!
    double cruiseAltitude_m() { return m_dCruiseAltitude_m; }

    //!
    double cruiseSpeed_ms() { return m_dCruiseSpeed_ms; }

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //!
    void update(double dDeltaTime);

    //!
    void nextWaypoint();

    //!
    void clearAllGeneratedWaypoints();

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    QVector<CWaypoint>      m_vWaypoints;
    double                  m_dClimbVerticalSpeed_ms;
    double                  m_dDescentVerticalSpeed_ms;
    double                  m_dCruiseAltitude_m;
    double                  m_dCruiseSpeed_ms;
};
