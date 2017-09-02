
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
    m_rTr1.setName(xNode.attributes()["Tr1"]);
    m_rTr2.setName(xNode.attributes()["Tr2"]);
    m_rDCBus1.setName(xNode.attributes()["DCBus1"]);
    m_rDCBus2.setName(xNode.attributes()["DCBus2"]);
    m_rDCBatBus.setName(xNode.attributes()["DCBatBus"]);
    m_rDCEssBus.setName(xNode.attributes()["DCEssBus"]);
}

//-------------------------------------------------------------------------------------------------

void CAirbusCFDIU::solveLinks(C3DScene* pScene)
{
    CAirbusFlightComputer::solveLinks(pScene);

    m_rGenerator1.solve(pScene, QSP<CComponent>(this));
    m_rGenerator2.solve(pScene, QSP<CComponent>(this));
    m_rACBus1.solve(pScene, QSP<CComponent>(this));
    m_rACBus2.solve(pScene, QSP<CComponent>(this));
    m_rTr1.solve(pScene, QSP<CComponent>(this));
    m_rTr2.solve(pScene, QSP<CComponent>(this));
    m_rDCBus1.solve(pScene, QSP<CComponent>(this));
    m_rDCBus2.solve(pScene, QSP<CComponent>(this));
    m_rDCBatBus.solve(pScene, QSP<CComponent>(this));
    m_rDCEssBus.solve(pScene, QSP<CComponent>(this));
}

//-------------------------------------------------------------------------------------------------

void CAirbusCFDIU::clearLinks(C3DScene* pScene)
{
    CAirbusFlightComputer::clearLinks(pScene);

    m_rGenerator1.clear();
    m_rGenerator2.clear();
    m_rACBus1.clear();
    m_rACBus2.clear();
    m_rTr1.clear();
    m_rTr2.clear();
    m_rDCBus1.clear();
    m_rDCBus2.clear();
    m_rDCBatBus.clear();
    m_rDCEssBus.clear();
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
    QSP<CElectricalBus> pTr1 = QSP_CAST(CElectricalBus, m_rTr1.component());
    QSP<CElectricalBus> pTr2 = QSP_CAST(CElectricalBus, m_rTr2.component());
    QSP<CElectricalBus> pDCBus1 = QSP_CAST(CElectricalBus, m_rDCBus1.component());
    QSP<CElectricalBus> pDCBus2 = QSP_CAST(CElectricalBus, m_rDCBus2.component());
    QSP<CElectricalBus> pDCBatBus = QSP_CAST(CElectricalBus, m_rDCBatBus.component());
    QSP<CElectricalBus> pDCEssBus = QSP_CAST(CElectricalBus, m_rDCEssBus.component());

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

    if (pTr1 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Tr1_Power_v, pTr1->load().m_dVoltage));
        pushData(CAirbusData(m_sName, adELEC_Tr1_Load_a, pTr1->load().m_dAmperage));
    }

    if (pTr2 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Tr2_Power_v, pTr2->load().m_dVoltage));
        pushData(CAirbusData(m_sName, adELEC_Tr2_Load_a, pTr2->load().m_dAmperage));
    }

    if (pDCBus1 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_DCBus1_Power_v, pDCBus1->load().m_dVoltage));
    }

    if (pDCBus2 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_DCBus2_Power_v, pDCBus2->load().m_dVoltage));
    }

    if (pDCBatBus != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_DCBatBus_Power_v, pDCBatBus->load().m_dVoltage));
    }

    if (pDCEssBus != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_DCEssBus_Power_v, pDCEssBus->load().m_dVoltage));
    }
}
