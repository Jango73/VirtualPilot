
// qt-plus
#include "CLogger.h"

// Quick3D
#include "C3DScene.h"

// Application
#include "CAirbusSEC.h"

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusSEC::instantiator(C3DScene* pScene)
{
    return new CAirbusSEC(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusSEC::CAirbusSEC(C3DScene* pScene)
    : CAirbusFlightComputer(pScene)
{
    LOG_DEBUG("CAirbusSEC::CAirbusSEC()");
}

//-------------------------------------------------------------------------------------------------

CAirbusSEC::~CAirbusSEC()
{
    LOG_DEBUG("CAirbusSEC::~CAirbusSEC()");
}

//-------------------------------------------------------------------------------------------------

void CAirbusSEC::update(double dDeltaTime)
{
    CAirbusFlightComputer::update(dDeltaTime);
}
