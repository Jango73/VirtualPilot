
// Qt
#include <QPainter>

// qt-plus
#include "CLogger.h"

// Quick3D
#include "C3DScene.h"

// Application
#include "CAirbusCFDIU.h"

//-------------------------------------------------------------------------------------------------

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusCFDIU::instanciator(C3DScene* pScene)
{
    return new CAirbusCFDIU(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusCFDIU::CAirbusCFDIU(C3DScene* pScene)
    : CAirbusFlightComputer(pScene)
{
    LOG_DEBUG("CAirbusCFDIU::CAirbusCFDIU()");
}

//-------------------------------------------------------------------------------------------------

CAirbusCFDIU::~CAirbusCFDIU()
{
    LOG_DEBUG("CAirbusCFDIU::~CAirbusCFDIU()");
}

//-------------------------------------------------------------------------------------------------

void CAirbusCFDIU::loadParameters(const QString& sBaseFile, CXMLNode xComponent)
{
    CAirbusFlightComputer::loadParameters(sBaseFile, xComponent);

    CXMLNode xNode = xComponent.getNodeByTagName(ParamName_Components);

    m_rGenerator1.setName(xNode.attributes()["Generator1"]);
    m_rGenerator2.setName(xNode.attributes()["Generator2"]);
    m_rACBus1.setName(xNode.attributes()["ACBus1"]);
    m_rACBus2.setName(xNode.attributes()["ACBus2"]);
}

//-------------------------------------------------------------------------------------------------

void CAirbusCFDIU::solveLinks(C3DScene* pScene)
{
    CAirbusFlightComputer::solveLinks(pScene);

    m_rGenerator1.solve(pScene, QSP<CComponent>(this));
    m_rGenerator2.solve(pScene, QSP<CComponent>(this));
    m_rACBus1.solve(pScene, QSP<CComponent>(this));
    m_rACBus2.solve(pScene, QSP<CComponent>(this));
}

//-------------------------------------------------------------------------------------------------

void CAirbusCFDIU::clearLinks(C3DScene* pScene)
{
    CAirbusFlightComputer::clearLinks(pScene);

    m_rGenerator1.clear();
    m_rGenerator2.clear();
    m_rACBus1.clear();
    m_rACBus2.clear();
}

//-------------------------------------------------------------------------------------------------

void CAirbusCFDIU::update(double dDeltaTime)
{
    CAirbusFlightComputer::update(dDeltaTime);
}

//-------------------------------------------------------------------------------------------------

void CAirbusCFDIU::work(double dDeltaTime)
{
    CAirbusFlightComputer::work(dDeltaTime);

    QSP<CEngineGenerator> pGen1 = QSP_CAST(CEngineGenerator, m_rGenerator1.component());
    QSP<CEngineGenerator> pGen2 = QSP_CAST(CEngineGenerator, m_rGenerator2.component());
    QSP<CElectricalBus> pACBus1 = QSP_CAST(CElectricalBus, m_rACBus1.component());
    QSP<CElectricalBus> pACBus2 = QSP_CAST(CElectricalBus, m_rACBus2.component());

    if (pGen1 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Gen1_Power_v, pGen1->current().m_dVoltage));
        pushData(CAirbusData(m_sName, adELEC_Gen1_Freq_hz, pGen1->current().m_dFrequency));
    }

    if (pGen2 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Gen2_Power_v, pGen2->current().m_dVoltage));
        pushData(CAirbusData(m_sName, adELEC_Gen2_Freq_hz, pGen2->current().m_dFrequency));
    }

    if (pACBus1 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_ACBus1_Power_v, pACBus1->load().m_dVoltage));
    }

    if (pACBus2 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_ACBus2_Power_v, pACBus2->load().m_dVoltage));
    }
}
