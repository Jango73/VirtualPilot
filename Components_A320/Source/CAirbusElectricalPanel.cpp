
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
    , m_bGenerator1_Online(false)
    , m_bGenerator2_Online(false)
{
}

//-------------------------------------------------------------------------------------------------

CAirbusElectricalPanel::~CAirbusElectricalPanel()
{
}

//-------------------------------------------------------------------------------------------------

void CAirbusElectricalPanel::update(double dDeltaTime)
{
    CAirbusFlightComputer::update(dDeltaTime);

    pushData(CAirbusData(m_sName, adELEC_Generator1_Online_bool, m_bGenerator1_Online));
    pushData(CAirbusData(m_sName, adELEC_Generator2_Online_bool, m_bGenerator2_Online));
}

//-------------------------------------------------------------------------------------------------

void CAirbusElectricalPanel::toggle_Generator1_Online()
{
    m_bGenerator1_Online = !m_bGenerator1_Online;
}

//-------------------------------------------------------------------------------------------------

void CAirbusElectricalPanel::toggle_Generator2_Online()
{
    m_bGenerator2_Online = !m_bGenerator2_Online;
}
