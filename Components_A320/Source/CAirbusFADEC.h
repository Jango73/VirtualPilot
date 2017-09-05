
#pragma once

// qt-plus
#include "CPIDController.h"

// Quick3D
#include "CComponentReference.h"
#include "CJetEngine.h"

// Application
#include "components_a320_global.h"
#include "CAirbusFlightComputer.h"
#include "Constants.h"

//-------------------------------------------------------------------------------------------------
// Forward declarations

class C3DScene;

//-------------------------------------------------------------------------------------------------

//! Full Authority Digital Engine Control
class COMPONENTS_A320_EXPORT CAirbusFADEC : public CAirbusFlightComputer
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    static CComponent* instantiator(C3DScene* pScene);

    //!
    CAirbusFADEC(C3DScene* pScene);

    //!
    virtual ~CAirbusFADEC();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Inherited methods
    //-------------------------------------------------------------------------------------------------

    //! Returns this object's class name
    virtual QString getClassName() const Q_DECL_OVERRIDE { return ClassName_CAirbusFADEC; }

    //! Loads this object's parameters
    virtual void loadParameters(const QString& sBaseFile, CXMLNode xComponent) Q_DECL_OVERRIDE;

    //! Solves the links of this object
    virtual void solveLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //! Deletes this object's links
    virtual void clearLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //!
    virtual void update(double dDeltaTime) Q_DECL_OVERRIDE;

    //!
    virtual void work(double dDeltaTime);

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    CComponentReference<CJetEngine>     m_rEngine1Target;
    CComponentReference<CJetEngine>     m_rEngine2Target;
};
