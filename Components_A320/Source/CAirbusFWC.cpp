
// qt-plus
#include "CLogger.h"

// Quick3D
#include "C3DScene.h"

// Application
#include "CAirbusFWC.h"

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusFWC::instantiator(C3DScene* pScene)
{
    return new CAirbusFWC(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusFWC::CAirbusFWC(C3DScene* pScene)
    : CAirbusFlightComputer(pScene)
{
}

//-------------------------------------------------------------------------------------------------

CAirbusFWC::~CAirbusFWC()
{
}

//-------------------------------------------------------------------------------------------------

void CAirbusFWC::update(double dDeltaTime)
{
    CAirbusFlightComputer::update(dDeltaTime);
}
