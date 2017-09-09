
#pragma once

// Application
#include "components_a320_global.h"
#include "CAirbusFlightComputer.h"
#include "Constants.h"

//-------------------------------------------------------------------------------------------------
// Forward declarations

class C3DScene;

//-------------------------------------------------------------------------------------------------

//! Flight Control Unit
//! Controls for autopilot and flight director
class COMPONENTS_A320_EXPORT CAirbusFCU : public CAirbusFlightComputer
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    static CComponent* instantiator(C3DScene* pScene);

    //!
    CAirbusFCU(C3DScene* pScene);

    //!
    virtual ~CAirbusFCU();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //!
    void setLateralManaged(bool bValue);

    //!
    void setVerticalManaged(bool bValue);

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Inherited methods
    //-------------------------------------------------------------------------------------------------

    //!
    virtual QString getClassName() const Q_DECL_OVERRIDE { return ClassName_CAirbusFCU; }

    //!
    virtual void update(double dDeltaTime) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //!
    void toggle_AutoPilot1_Engaged();

    //!
    void toggle_AutoPilot2_Engaged();

    //!
    void toggle_AutoThrust_Engaged();

    //!
    void increment_SelectedHeading(bool bFast);

    //!
    void decrement_SelectedHeading(bool bFast);

    //!
    void increment_SelectedAltitude(bool bFast);

    //!
    void decrement_SelectedAltitude(bool bFast);

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    bool    m_bAutoPilot1_Engaged;
    bool    m_bAutoPilot2_Engaged;
    bool    m_bAutoThrust_Engaged;
    bool    m_bLateralManaged;
    bool    m_bVerticalManaged;

    double  m_dSelectedHeading;
    double  m_dSelectedAltitude_m;
    double  m_dSelectedVelocity_ms;
};
