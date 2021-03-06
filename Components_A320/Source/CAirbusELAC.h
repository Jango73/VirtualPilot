
#pragma once

// qt-plus
#include "CPIDController.h"

// Quick3D
#include "CComponentReference.h"
#include "CWing.h"
#include "CElevator.h"
#include "CVector2.h"

// Application
#include "components_a320_global.h"
#include "CAirbusFlightComputer.h"
#include "Constants.h"

//-------------------------------------------------------------------------------------------------

class C3DScene;

//-------------------------------------------------------------------------------------------------

//! Elevator and Aileron Computer
class COMPONENTS_A320_EXPORT CAirbusELAC : public CAirbusFlightComputer
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    static CComponent* instantiator(C3DScene* pScene);

    //!
    CAirbusELAC(C3DScene* pScene);

    //!
    virtual ~CAirbusELAC();

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
    virtual QString getClassName() const Q_DECL_OVERRIDE { return ClassName_CAirbusELAC; }

    //! Loads this object's parameters
    virtual void loadParameters(const QString& sBaseFile, const CXMLNode& xComponent) Q_DECL_OVERRIDE;

    //! Solves the links of this object
    virtual void solveLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //! Deletes this object's links
    virtual void clearLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //!
    virtual void update(double dDeltaTime) Q_DECL_OVERRIDE;

    //!
    virtual void work(double dDeltaTime) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    CComponentReference<CWing>		m_rLeftWingTarget;
    CComponentReference<CWing>		m_rRightWingTarget;
    CComponentReference<CElevator>	m_rElevatorTarget;

    CPIDController					m_pidYaw;
    CPIDController					m_pidPitch;
    CPIDController					m_pidRoll;

    Math::CVector2					m_vStick;
    Math::CVector2					m_vStickPrevious;
    Math::CVector3					m_vCommandedAttitude;

    double                          m_dMaxRoll_deg;
};
