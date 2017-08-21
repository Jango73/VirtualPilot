
#pragma once

// Application
#include "components_a320_global.h"
#include "CAirbusComponent.h"
#include "CAirbusDataSupplier.h"
#include "Constants.h"

//-------------------------------------------------------------------------------------------------

class COMPONENTS_A320_EXPORT CAirbusPitotPort : public CComponent, public CAirbusComponent, public CAirbusDataSupplier
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    static CComponent* instanciator(C3DScene* pScene);

    //!
    CAirbusPitotPort(C3DScene* pScene);

    //!
    virtual ~CAirbusPitotPort();

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
    virtual QString getClassName() const { return ClassName_CAirbusPitotPort; }

    //!
    virtual void update(double dDeltaTime) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:
};