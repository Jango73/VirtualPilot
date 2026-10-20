
// CFM56 turbofan engine, as fitted on the Airbus A320.
// Idle N1 is 25%, full fuel flow gives 100% N1.

#pragma once

// Quick3D
#include "CJetEngine.h"

// Application
#include "components_a320_global.h"
#include "Constants.h"

//-------------------------------------------------------------------------------------------------
// Forward declarations

class C3DScene;

//-------------------------------------------------------------------------------------------------

//! CFM56 turbofan engine
class COMPONENTS_A320_EXPORT CCFM56Engine : public CJetEngine
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    static CComponent* instantiator(C3DScene* pScene);

    //!
    CCFM56Engine(C3DScene* pScene);

    //!
    virtual ~CCFM56Engine();

    //-------------------------------------------------------------------------------------------------
    // Overridden methods
    //-------------------------------------------------------------------------------------------------

    //! Returns this object's class name
    virtual QString getClassName() const Q_DECL_OVERRIDE { return ClassName_CCFM56Engine; }

    //! Returns thrust in kilograms
    virtual double currentThrust_kg() const Q_DECL_OVERRIDE;

    //! Updates this object using the elapsed time since last update
    virtual void update(double dDeltaTime) Q_DECL_OVERRIDE;
};
