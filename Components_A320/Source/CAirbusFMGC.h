
#pragma once

// qt-plus
#include "CPIDController.h"

// Application
#include "components_a320_global.h"
#include "CAirbusFlightComputer.h"
#include "CAirbusFlightPlan.h"
#include "Constants.h"

//-------------------------------------------------------------------------------------------------
// Forward declarations

class C3DScene;

//-------------------------------------------------------------------------------------------------
// Values used to check flight phase changes

#define FP_TAXI_THRUST_THRESHOLD            (0.5)
#define FP_TAKEOFF_ALTITUDE_AGL_THRESHOLD   (30.0 * FAC_FEET_TO_METERS)
#define FP_CLIMB_ALTITUDE_THRESHOLD         (500.0 * FAC_FEET_TO_METERS)
#define FP_CRUISE_VERTSPEED_THRESHOLD       (500.0 * FAC_FPM_TO_MS)
#define FP_CRUISE_ALTITUDE_AGL_THRESHOLD    (500.0 * FAC_FEET_TO_METERS)
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
    static CComponent* instanciator(C3DScene* pScene);

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
    // Inherited methods
    //-------------------------------------------------------------------------------------------------

    //!
    virtual QString getClassName() const { return ClassName_CAirbusFMGC; }

    //!
    virtual void update(double dDeltaTime) Q_DECL_OVERRIDE;

    //!
    virtual void work(double dDeltaTime);

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

    EAirbusFlightPhase      m_eFlightPhase;
    EAirbusLateralMode      m_eLateralMode;
    EAirbusVerticalMode     m_eVerticalMode;
    CAirbusFlightPlan       m_tFlightPlan;
    double                  m_dDeltaTime;
    double                  m_dPreviousAircraftVerticalSpeed_ms;

    // Commandes latérales
    double                  m_dCommandedHeading_deg;        // Commande de cap en degrés
    double                  m_dCommandedRoll_deg;           // Commande de roulis en degrés
    double                  m_dCommandedRollVelocity_ds;

    // Commandes verticales
    double                  m_dCommandedVerticalSpeed_ms;
    double                  m_dCommandedAltitude_m;
    double                  m_dCommandedPitch_deg;
    double                  m_dCommandedPitchVelocity_ds;

    CPIDController          m_pidVerticalSpeed;

    // Commandes de poussée
    double                  m_dCommandedVelocity_ms;
    double                  m_dCommandedAcceleration_ms;
    double                  m_dCommandedThrust_norm;

    CPIDController          m_pidAcceleration;
    CPIDController          m_pidDeceleration;

    QDateTime               m_tLastUpdate;
};
