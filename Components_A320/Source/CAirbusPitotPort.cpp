
// qt-plus
#include "CLogger.h"

// Quick3D
#include "C3DScene.h"

// Application
#include "CAirbusPitotPort.h"

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusPitotPort::instantiator(C3DScene* pScene)
{
    return new CAirbusPitotPort(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusPitotPort::CAirbusPitotPort(C3DScene* pScene)
    : CComponent(pScene)
{
    LOG_DEBUG("CAirbusPitotPort::CAirbusPitotPort()");
}

//-------------------------------------------------------------------------------------------------

CAirbusPitotPort::~CAirbusPitotPort()
{
    LOG_DEBUG("CAirbusPitotPort::~CAirbusPitotPort()");
}

//-------------------------------------------------------------------------------------------------

void CAirbusPitotPort::update(double dDeltaTime)
{
}
