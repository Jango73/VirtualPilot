
// qt-plus
#include "CLogger.h"

// Quick3D
#include "C3DScene.h"

// Application
#include "CAirbusFCU.h"

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusFCU::instantiator(C3DScene* pScene)
{
    return new CAirbusFCU(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusFCU::CAirbusFCU(C3DScene* pScene)
    : CAirbusFlightComputer(pScene)
    , m_bAutoPilot1_Engaged(false)
    , m_bAutoPilot2_Engaged(false)
    , m_bAutoThrust_Engaged(false)
    , m_bLateralManaged(true)
    , m_bVerticalManaged(true)
    , m_dSelectedHeading(0.0)
    , m_dSelectedAltitude_m(10000.0 * FAC_FEET_TO_METERS)
    , m_dSelectedVelocity_ms(200.0 * FAC_KNOTS_TO_MS)
{
}

//-------------------------------------------------------------------------------------------------

CAirbusFCU::~CAirbusFCU()
{
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCU::setLateralManaged(bool bValue)
{
    m_bLateralManaged = bValue;
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCU::setVerticalManaged(bool bValue)
{
    m_bVerticalManaged = bValue;
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCU::update(double dDeltaTime)
{
    CAirbusFlightComputer::update(dDeltaTime);

    pushData(CAirbusData(m_sName, adFCU_AutoPilot1_Engaged_bool, m_bAutoPilot1_Engaged));
    pushData(CAirbusData(m_sName, adFCU_AutoPilot2_Engaged_bool, m_bAutoPilot2_Engaged));
    pushData(CAirbusData(m_sName, adFCU_AutoThrust_Engaged_bool, m_bAutoThrust_Engaged));
    pushData(CAirbusData(m_sName, adFCU_Lateral_Managed_bool, m_bLateralManaged));
    pushData(CAirbusData(m_sName, adFCU_Vertical_Managed_bool, m_bVerticalManaged));

    pushData(CAirbusData(m_sName, adFCU_Altitude_f, m_dSelectedAltitude_m));
    pushData(CAirbusData(m_sName, adFCU_Heading_deg, m_dSelectedHeading));
    pushData(CAirbusData(m_sName, adFCU_Airspeed_ms, m_dSelectedVelocity_ms));
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCU::toggle_AutoPilot1_Engaged()
{
    m_bAutoPilot1_Engaged = !m_bAutoPilot1_Engaged;
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCU::toggle_AutoPilot2_Engaged()
{
    m_bAutoPilot2_Engaged = !m_bAutoPilot2_Engaged;
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCU::toggle_AutoThrust_Engaged()
{
    m_bAutoThrust_Engaged = !m_bAutoThrust_Engaged;
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCU::increment_SelectedHeading(bool bFast)
{
    m_dSelectedHeading++;

    m_dSelectedHeading = Math::Angles::clipAngleDegree(m_dSelectedHeading);
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCU::decrement_SelectedHeading(bool bFast)
{
    m_dSelectedHeading--;

    m_dSelectedHeading = Math::Angles::clipAngleDegree(m_dSelectedHeading);
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCU::increment_SelectedAltitude(bool bFast)
{
    m_dSelectedAltitude_m += 100.0 * FAC_FEET_TO_METERS;

    m_dSelectedAltitude_m = Math::Angles::clipDouble(m_dSelectedAltitude_m, 0.0, 90000.0 * FAC_FEET_TO_METERS);
}

//-------------------------------------------------------------------------------------------------

void CAirbusFCU::decrement_SelectedAltitude(bool bFast)
{
    m_dSelectedAltitude_m -= 100.0 * FAC_FEET_TO_METERS;

    m_dSelectedAltitude_m = Math::Angles::clipDouble(m_dSelectedAltitude_m, 0.0, 90000.0 * FAC_FEET_TO_METERS);
}
