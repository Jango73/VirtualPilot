
// qt-plus
#include "CLogger.h"

// Quick3D
#include "C3DScene.h"

// Application
#include "CAirbusFCC.h"

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusFCC::instantiator(C3DScene* pScene)
{
    return new CAirbusFCC(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusFCC::CAirbusFCC(C3DScene* pScene)
    : CAirbusFlightComputer(pScene)
    , m_eFlightLaw(flNormal)
{
    LOG_DEBUG("CAirbusFCC::CAirbusFCC()");
}

//-------------------------------------------------------------------------------------------------

CAirbusFCC::~CAirbusFCC()
{
    LOG_DEBUG("CAirbusFCC::~CAirbusFCC()");
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCC::update(double dDeltaTime)
{
    CAirbusFlightComputer::update(dDeltaTime);
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCC::work(double dDeltaTime)
{
    bool bGear_OnGround_bool = GETDATA_BOOL(adGear_OnGround_bool);

    // Compute flight law
}
