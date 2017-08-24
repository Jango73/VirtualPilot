
#pragma once

// Application
#include "components_a320_global.h"
#include "CAirbusFlightComputer.h"
#include "Constants.h"

//-------------------------------------------------------------------------------------------------

class C3DScene;

class COMPONENTS_A320_EXPORT CAirbusFCU : public CAirbusFlightComputer
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    static CComponent* instanciator(C3DScene* pScene);

    //!
    CAirbusFCU(C3DScene* pScene);

    //!
    virtual ~CAirbusFCU();

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
    virtual QString getClassName() const { return ClassName_CAirbusFCU; }

    //!
    virtual void update(double dDeltaTime) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //
    void toggle_AutoPilot1_Engaged();

    //
    void toggle_AutoPilot2_Engaged();

    //
    void toggle_AutoThrust_Engaged();

    //
    void increment_SelectedHeading(bool bFast);

    //
    void decrement_SelectedHeading(bool bFast);

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    bool	m_bAutoPilot1_Engaged;
    bool	m_bAutoPilot2_Engaged;
    bool	m_bAutoThrust_Engaged;

    double	m_dSelectedHeading;
    double  m_dSelectedAltitude;
};
