
// qt-plus
#include "CLogger.h"

// Quick3D
#include "C3DScene.h"
#include "CAircraft.h"

// Application
#include "CAirbusGearSensor.h"

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusGearSensor::instantiator(C3DScene* pScene)
{
    return new CAirbusGearSensor(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusGearSensor::CAirbusGearSensor(C3DScene* pScene)
    : CComponent(pScene)
{
}

//-------------------------------------------------------------------------------------------------

CAirbusGearSensor::~CAirbusGearSensor()
{
}

//-------------------------------------------------------------------------------------------------

void CAirbusGearSensor::update(double dDeltaTime)
{
    QSP<CAircraft> pAircraft = QSP_CAST(CAircraft, root());

    if (pAircraft != nullptr)
    {
        bool bOnGround = pAircraft->onGround();

        pushData(CAirbusData(m_sName, adGear_OnGround_bool, bOnGround));
    }
}
