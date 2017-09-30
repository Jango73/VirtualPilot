
// qt-plus
#include "CLogger.h"

// Quick3D
#include "CConsoleBoard.h"
#include "C3DScene.h"
#include "CWing.h"
#include "CElevator.h"
#include "CJetEngine.h"

// Application
#include "CAirbusFADEC.h"

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusFADEC::instantiator(C3DScene* pScene)
{
    return new CAirbusFADEC(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusFADEC::CAirbusFADEC(C3DScene* pScene)
    : CAirbusFlightComputer(pScene)
{
}

//-------------------------------------------------------------------------------------------------

CAirbusFADEC::~CAirbusFADEC()
{
}

//-------------------------------------------------------------------------------------------------

void CAirbusFADEC::loadParameters(const QString& sBaseFile, const CXMLNode& xComponent)
{
    CAirbusFlightComputer::loadParameters(sBaseFile, xComponent);

    CXMLNode xNode = xComponent.getNodeByTagName(ParamName_Engines);

    m_rEngine1Target.setName(xNode.attributes()[ParamName_Engine1Target]);
    m_rEngine2Target.setName(xNode.attributes()[ParamName_Engine2Target]);
}

//-------------------------------------------------------------------------------------------------

void CAirbusFADEC::solveLinks(C3DScene* pScene)
{
    CAirbusFlightComputer::solveLinks(pScene);

    m_rEngine1Target.solve(pScene, QSP<CComponent>(this));
    m_rEngine2Target.solve(pScene, QSP<CComponent>(this));
}

//-------------------------------------------------------------------------------------------------

void CAirbusFADEC::clearLinks(C3DScene* pScene)
{
    CAirbusFlightComputer::clearLinks(pScene);

    m_rEngine1Target.clear();
    m_rEngine2Target.clear();
}

//-------------------------------------------------------------------------------------------------

void CAirbusFADEC::update(double dDeltaTime)
{
    CAirbusFlightComputer::update(dDeltaTime);
}

//-------------------------------------------------------------------------------------------------

void CAirbusFADEC::work(double dDeltaTime)
{
    CAirbusFlightComputer::work(dDeltaTime);

    QSP<CJetEngine> pEngine1 = QSP_CAST(CJetEngine, m_rEngine1Target.component());
    QSP<CJetEngine> pEngine2 = QSP_CAST(CJetEngine, m_rEngine2Target.component());

    if (pEngine1 != nullptr && pEngine2 != nullptr )
    {
        double dFG_CommandedThrust_norm = GETDATA_DOUBLE(adFG_CommandedThrust_norm);
        bool bFCU_AutoThrust_Engaged = GETDATA_BOOL(adFCU_AutoThrust_Engaged_bool);
        double dThrottle_1_norm = GETDATA_DOUBLE(adThrottle_1_norm);
        double dThrottle_2_norm = GETDATA_DOUBLE(adThrottle_2_norm);

        if (bFCU_AutoThrust_Engaged == true)
        {
            pEngine1->setCurrentFuelFlow_norm(dFG_CommandedThrust_norm);
            pEngine2->setCurrentFuelFlow_norm(dFG_CommandedThrust_norm);
        }
        else
        {
            pEngine1->setCurrentFuelFlow_norm(dThrottle_1_norm);
            pEngine2->setCurrentFuelFlow_norm(dThrottle_2_norm);
        }

        pushData(CAirbusData(m_sName, adFADEC_Engine1_N1_norm, pEngine1->n1_norm()));
        pushData(CAirbusData(m_sName, adFADEC_Engine2_N1_norm, pEngine2->n1_norm()));
    }
}
