
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

CComponent* CAirbusCFDIU::instantiator(C3DScene* pScene)
{
    return new CAirbusCFDIU(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusCFDIU::CAirbusCFDIU(C3DScene* pScene)
    : CAirbusFlightComputer(pScene)
{
}

//-------------------------------------------------------------------------------------------------

CAirbusCFDIU::~CAirbusCFDIU()
{
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
    m_rEssTr.setName(xNode.attributes()["EssTr"]);
    m_rDCBus1.setName(xNode.attributes()["DCBus1"]);
    m_rDCBus2.setName(xNode.attributes()["DCBus2"]);
    m_rDCBatBus.setName(xNode.attributes()["DCBatBus"]);
    m_rDCEssBus.setName(xNode.attributes()["DCEssBus"]);
    m_rACEssBus.setName(xNode.attributes()["ACEssBus"]);

    m_rContGen1.setName(xNode.attributes()["ContGen1"]);
    m_rContGen2.setName(xNode.attributes()["ContGen2"]);
    m_rContGenAPU.setName(xNode.attributes()["ContGenAPU"]);
    m_rContACTie1.setName(xNode.attributes()["ContACTie1"]);
    m_rContACTie2.setName(xNode.attributes()["ContACTie2"]);
    m_rContTr1.setName(xNode.attributes()["ContTr1"]);
    m_rContTr2.setName(xNode.attributes()["ContTr2"]);
    m_rContDCTie1.setName(xNode.attributes()["ContDCTie1"]);
    m_rContDCTie2.setName(xNode.attributes()["ContDCTie2"]);
    m_rContEssTr.setName(xNode.attributes()["ContEssTr"]);
    m_rContACEssFeed1.setName(xNode.attributes()["ContACEssFeed1"]);
    m_rContACEssFeed2.setName(xNode.attributes()["ContACEssFeed2"]);
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
    m_rEssTr.solve(pScene, QSP<CComponent>(this));
    m_rDCBus1.solve(pScene, QSP<CComponent>(this));
    m_rDCBus2.solve(pScene, QSP<CComponent>(this));
    m_rDCBatBus.solve(pScene, QSP<CComponent>(this));
    m_rDCEssBus.solve(pScene, QSP<CComponent>(this));
    m_rACEssBus.solve(pScene, QSP<CComponent>(this));

    m_rContGen1.solve(pScene, QSP<CComponent>(this));
    m_rContGen2.solve(pScene, QSP<CComponent>(this));
    m_rContGenAPU.solve(pScene, QSP<CComponent>(this));
    m_rContACTie1.solve(pScene, QSP<CComponent>(this));
    m_rContACTie2.solve(pScene, QSP<CComponent>(this));
    m_rContTr1.solve(pScene, QSP<CComponent>(this));
    m_rContTr2.solve(pScene, QSP<CComponent>(this));
    m_rContDCTie1.solve(pScene, QSP<CComponent>(this));
    m_rContDCTie2.solve(pScene, QSP<CComponent>(this));
    m_rContEssTr.solve(pScene, QSP<CComponent>(this));
    m_rContACEssFeed1.solve(pScene, QSP<CComponent>(this));
    m_rContACEssFeed2.solve(pScene, QSP<CComponent>(this));
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
    m_rEssTr.clear();
    m_rDCBus1.clear();
    m_rDCBus2.clear();
    m_rDCBatBus.clear();
    m_rDCEssBus.clear();
    m_rACEssBus.clear();

    m_rContGen1.clear();
    m_rContGen2.clear();
    m_rContGenAPU.clear();
    m_rContACTie1.clear();
    m_rContACTie2.clear();
    m_rContTr1.clear();
    m_rContTr2.clear();
    m_rContDCTie1.clear();
    m_rContDCTie2.clear();
    m_rContEssTr.clear();
    m_rContACEssFeed1.clear();
    m_rContACEssFeed2.clear();
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
    QSP<CElectricalBus> pEssTr = QSP_CAST(CElectricalBus, m_rEssTr.component());
    QSP<CElectricalBus> pDCBus1 = QSP_CAST(CElectricalBus, m_rDCBus1.component());
    QSP<CElectricalBus> pDCBus2 = QSP_CAST(CElectricalBus, m_rDCBus2.component());
    QSP<CElectricalBus> pDCBatBus = QSP_CAST(CElectricalBus, m_rDCBatBus.component());
    QSP<CElectricalBus> pDCEssBus = QSP_CAST(CElectricalBus, m_rDCEssBus.component());
    QSP<CElectricalBus> pACEssBus = QSP_CAST(CElectricalBus, m_rACEssBus.component());

    QSP<CElectricalContactor> pContGen1 = QSP_CAST(CElectricalContactor, m_rContGen1.component());
    QSP<CElectricalContactor> pContGen2 = QSP_CAST(CElectricalContactor, m_rContGen2.component());
    QSP<CElectricalContactor> pContGenAPU = QSP_CAST(CElectricalContactor, m_rContGenAPU.component());
    QSP<CElectricalContactor> pContACTie1 = QSP_CAST(CElectricalContactor, m_rContACTie1.component());
    QSP<CElectricalContactor> pContACTie2 = QSP_CAST(CElectricalContactor, m_rContACTie2.component());
    QSP<CElectricalContactor> pContTr1 = QSP_CAST(CElectricalContactor, m_rContTr1.component());
    QSP<CElectricalContactor> pContTr2 = QSP_CAST(CElectricalContactor, m_rContTr2.component());
    QSP<CElectricalContactor> pContDCTie1 = QSP_CAST(CElectricalContactor, m_rContDCTie1.component());
    QSP<CElectricalContactor> pContDCTie2 = QSP_CAST(CElectricalContactor, m_rContDCTie2.component());
    QSP<CElectricalContactor> pContEssTr = QSP_CAST(CElectricalContactor, m_rContEssTr.component());
    QSP<CElectricalContactor> pContACEssFeed1 = QSP_CAST(CElectricalContactor, m_rContACEssFeed1.component());
    QSP<CElectricalContactor> pContACEssFeed2 = QSP_CAST(CElectricalContactor, m_rContACEssFeed2.component());

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

    if (pEssTr != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_EssTr_Power_v, pEssTr->load().m_dVoltage));
        pushData(CAirbusData(m_sName, adELEC_EssTr_Load_a, pEssTr->load().m_dAmperage));
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

    if (pACEssBus != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_ACEssBus_Power_v, pACEssBus->load().m_dVoltage));
    }

    if (pContGen1 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Cont_Gen1_bool, pContGen1->closed()));
    }

    if (pContGen2 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Cont_Gen2_bool, pContGen2->closed()));
    }

    if (pContGenAPU != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Cont_GenAPU_bool, pContGenAPU->closed()));
    }

    if (pContACTie1 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Cont_ACTie1_bool, pContACTie1->closed()));
    }

    if (pContACTie2 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Cont_ACTie2_bool, pContACTie2->closed()));
    }

    if (pContTr1 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Cont_Tr1_bool, pContTr1->closed()));
    }

    if (pContTr2 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Cont_Tr2_bool, pContTr2->closed()));
    }

    if (pContDCTie1 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Cont_DCTie1_bool, pContDCTie1->closed()));
    }

    if (pContDCTie2 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Cont_DCTie2_bool, pContDCTie2->closed()));
    }

    if (pContEssTr != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Cont_EssTr_bool, pContEssTr->closed()));
    }

    if (pContACEssFeed1 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Cont_ACEssFeed_1_bool, pContACEssFeed1->closed()));
    }

    if (pContACEssFeed2 != nullptr)
    {
        pushData(CAirbusData(m_sName, adELEC_Cont_ACEssFeed_2_bool, pContACEssFeed2->closed()));
    }
}
