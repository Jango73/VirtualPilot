
#pragma once

// qt-plus
#include "CPIDController.h"

// Quick3D
#include "CComponentReference.h"

// Application
#include "components_a320_global.h"
#include "CAirbusFlightComputer.h"
#include "CAirbusFlightPlan.h"
#include "Constants.h"
#include "../../Components_Generic/Source/CNavaidDatabase.h"

//-------------------------------------------------------------------------------------------------
// Forward declarations

class C3DScene;

//-------------------------------------------------------------------------------------------------
// Values used to check flight phase changes

#define FP_TAXI_THRUST_THRESHOLD            (0.5)
#define FP_TAKEOFF_ALTITUDE_AGL_THRESHOLD   (30.0 * FAC_FEET_TO_METERS)
#define FP_CLIMB_ALTITUDE_THRESHOLD         (500.0 * FAC_FEET_TO_METERS)
#define FP_CRUISE_VERTSPEED_THRESHOLD       (500.0 * FAC_FPM_TO_MS)
#define FP_DESCENT_ALTITUDE_AGL_THRESHOLD   (2500.0 * FAC_FEET_TO_METERS)
#define FP_LAND_GROUNDSPEED_THRESHOLD       (50.0 * FAC_KNOTS_TO_MS)

//-------------------------------------------------------------------------------------------------

//! Flight Managment and Guidance Computer
//! Manages flight and autopilot
class COMPONENTS_A320_EXPORT CAirbusFMGC : public CAirbusFlightComputer
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    static CComponent* instantiator(C3DScene* pScene);

    //!
    CAirbusFMGC(C3DScene* pScene);

    //!
    virtual ~CAirbusFMGC();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Overridden methods
    //-------------------------------------------------------------------------------------------------

    //!
    virtual QString getClassName() const Q_DECL_OVERRIDE { return ClassName_CAirbusFMGC; }

    //! Loads this object's parameters
    virtual void loadParameters(const QString& sBaseFile, CXMLNode xComponent) Q_DECL_OVERRIDE;

    //! Solves the links of this object
    virtual void solveLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //! Deletes this object's links
    virtual void clearLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //! Updates this object
    virtual void update(double dDeltaTime) Q_DECL_OVERRIDE;

    //! Does computer work
    virtual void work(double dDeltaTime) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //!
    void loadFlightPlan();

    //!
    void work_FM(double dDeltaTime);

    //!
    void work_FM_ProcessMCDUData(double dDeltaTime);

    //!
    void work_FM_doPredictions(double dDeltaTime);

    //!
    void work_FG(double dDeltaTime);

    //!
    void computeFlightPhase(double dDeltaTime);

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    CComponentReference<CNavaidDatabase>    m_rNavaids;                         // Reference to navaid database

    EAirbusFlightPhase                      m_eFlightPhase;                     // Current flight phase
    EAirbusLateralMode                      m_eLateralMode;                     // Current lateral mode
    EAirbusVerticalMode                     m_eVerticalMode;                    // Current vertical mode
    CAirbusFlightPlan                       m_tFlightPlan;                      // Primary flight plan
    QDateTime                               m_tLastUpdate;                      // Last time of update
    double                                  m_dDeltaTime;
    double                                  m_dPreviousAircraftVerticalSpeed_ms;

    // Lateral commands
    double                                  m_dCommandedHeading_deg;            // Heading command in degrees
    double                                  m_dCommandedRoll_deg;               // Roll command in degrees
    double                                  m_dCommandedRollVelocity_ds;        // Roll velocity command in degrees per second

    // Vertical commands
    double                                  m_dCommandedVerticalSpeed_ms;       // Vertical speed command in meters per second
    double                                  m_dCommandedAltitude_m;             // Altitude command in meters
    double                                  m_dCommandedPitch_deg;              // Pitch command in degrees
    double                                  m_dCommandedPitchVelocity_ds;       // Pitch velocity command in degrees per second
    CPIDController                          m_pidVerticalSpeed;                 // Vertical speed controller

    // Thrust commands
    double                                  m_dCommandedAirspeed_ms;            // Airspeed command in meters per second
    double                                  m_dCommandedAcceleration_ms;        // Acceleration command in meters per second
    double                                  m_dCommandedThrust_norm;            // Thrust command normalized
    CPIDController                          m_pidAcceleration;                  // Acceleration controller
    CPIDController                          m_pidDeceleration;                  // Deceleration controller
};
