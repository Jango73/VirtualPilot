
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
}

//-------------------------------------------------------------------------------------------------

CAirbusFCC::~CAirbusFCC()
{
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCC::update(double dDeltaTime)
{
    CAirbusFlightComputer::update(dDeltaTime);
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCC::work(double dDeltaTime)
{
    work_FlightLaws(dDeltaTime);
    work_Electrical(dDeltaTime);
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCC::work_FlightLaws(double dDeltaTime)
{
    bool bGear_OnGround_bool = GETDATA_BOOL(adGear_OnGround_bool);
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCC::work_Electrical(double dDeltaTime)
{
}
