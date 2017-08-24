
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

    //!
    void setCompanyRoute(const QString& sValue);

    //!
    void setICAOFrom(const QString& sValue);

    //!
    void setICAOTo(const QString& sValue);

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //!
    QVector<CWaypoint>& waypoints() { return m_vWaypoints; }

    //!
    CWaypoint& lastWaypoint() { return m_vWaypoints.last(); }

    //!
    double climbVerticalSpeed_ms() const { return m_dClimbVerticalSpeed_ms; }

    //!
    double descentVerticalSpeed_ms() const { return m_dDescentVerticalSpeed_ms; }

    //!
    double cruiseAltitude_m() const { return m_dCruiseAltitude_m; }

    //!
    double cruiseSpeed_ms() const { return m_dCruiseSpeed_ms; }

    //!
    QString companyRoute() const { return m_sCompanyRoute; }

    //!
    QString ICAOFrom() const { return m_sICAOFrom; }

    //!
    QString ICAOTo() const { return m_sICAOTo; }

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
    QString                 m_sCompanyRoute;
    QString                 m_sICAOFrom;
    QString                 m_sICAOTo;
};
