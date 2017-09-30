
#pragma once

// Quick3D
#include "CElectricalConsumer.h"

// Application
#include "components_a320_global.h"
#include "CAirbusComponent.h"
#include "CAirbusDataSupplier.h"
#include "Constants.h"

//-------------------------------------------------------------------------------------------------

class C3DScene;

class COMPONENTS_A320_EXPORT CAirbusFlightComputer : public CElectricalConsumer, public CAirbusComponent, public CAirbusDataSupplier
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    static CComponent* instantiator(C3DScene* pScene);

    //!
    CAirbusFlightComputer(C3DScene* pScene);

    //!
    virtual ~CAirbusFlightComputer();

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
    virtual QString getClassName() const Q_DECL_OVERRIDE { return ClassName_CAirbusFlightComputer; }

    //! Loads this object's parameters
    virtual void loadParameters(const QString& sBaseFile, const CXMLNode& xComponent) Q_DECL_OVERRIDE;

    //! Solves the links of this object
    virtual void solveLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //! Deletes this object's links
    virtual void clearLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //! Updates this object
    virtual void update(double dDeltaTime) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Does computer work
    virtual void work(double dDeltaTime);

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    int     m_iUnitIndex;
};
