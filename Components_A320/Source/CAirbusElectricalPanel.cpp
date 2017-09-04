
// qt-plus
#include "CLogger.h"

// Quick3D
#include "C3DScene.h"

// Application
#include "CAirbusElectricalPanel.h"

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusElectricalPanel::instantiator(C3DScene* pScene)
{
    return new CAirbusElectricalPanel(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusElectricalPanel::CAirbusElectricalPanel(C3DScene* pScene)
    : CAirbusFlightComputer(pScene)
    , m_bValue1(false)
{
    LOG_DEBUG("CAirbusElectricalPanel::CAirbusElectricalPanel()");
}

//-------------------------------------------------------------------------------------------------

CAirbusElectricalPanel::~CAirbusElectricalPanel()
{
    LOG_DEBUG("CAirbusElectricalPanel::~CAirbusElectricalPanel()");
}

//-------------------------------------------------------------------------------------------------

void CAirbusElectricalPanel::update(double dDeltaTime)
{
    CAirbusFlightComputer::update(dDeltaTime);

    // pushData(CAirbusData(m_sName, adFCU_AutoPilot1_Engaged, m_bAutoPilot1_Engaged));
}

//-------------------------------------------------------------------------------------------------

void CAirbusElectricalPanel::toggle_Value1()
{
    m_bValue1 = !m_bValue1;
}
