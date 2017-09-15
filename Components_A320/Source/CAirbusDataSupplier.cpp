
// qt-plus
#include "CLogger.h"

// Quick3D
#include "C3DScene.h"

// Application
#include "CAirbusDataSupplier.h"

//-------------------------------------------------------------------------------------------------

CAirbusDataSupplier::CAirbusDataSupplier()
{
}

//-------------------------------------------------------------------------------------------------

CAirbusDataSupplier::~CAirbusDataSupplier()
{
}

//-------------------------------------------------------------------------------------------------

CAirbusData* CAirbusDataSupplier::data(EAirbusData eID)
{
    for (int iIndex = 0; iIndex < m_vDataIncoming.count(); iIndex++)
    {
        if (m_vDataIncoming[iIndex].ID() == eID)
        {
            return &(m_vDataIncoming[iIndex]);
        }
    }

    return nullptr;
}

//-------------------------------------------------------------------------------------------------

bool CAirbusDataSupplier::dataValid(EAirbusData eID)
{
    return true;
}

//-------------------------------------------------------------------------------------------------

void CAirbusDataSupplier::loadParameters(const QString& sBaseFile, CXMLNode xComponent)
{
    QVector<CXMLNode> vInputsNodes = xComponent.getNodesByTagName("DataInput");

    foreach (CXMLNode xInput, vInputsNodes)
    {
        if (xInput.attributes()[ParamName_Name].isEmpty() == false)
        {
            m_vDataInputNames.append(xInput.attributes()[ParamName_Name]);
        }
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusDataSupplier::solveLinks(C3DScene* pScene)
{
}

//-------------------------------------------------------------------------------------------------

void CAirbusDataSupplier::clearLinks(C3DScene* pScene)
{
    foreach (CAirbusDataSupplier* pInput, m_vDataInputs)
    {
        pInput->m_vDataOutputs.removeAll(this);
        m_vDataInputs.removeAll(pInput);
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusDataSupplier::solveLinks(C3DScene* pScene, CComponent* pCaller)
{
    foreach (QString sName, m_vDataInputNames)
    {
        foreach (QSP<CComponent> pComponent, pScene->components())
        {
            QSP<CComponent> pFound = pComponent->findComponent(sName, QSP<CComponent>(pCaller));

            if (pFound != nullptr)
            {
                CAirbusDataSupplier* pInput = dynamic_cast<CAirbusDataSupplier*>(pFound.data());

                if (pInput != nullptr)
                {
                    m_vDataInputs.append(pInput);
                    pInput->m_vDataOutputs.append(this);
                }

                break;
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusDataSupplier::pushData(CAirbusData outgoingData)
{
    for (int iIndex = 0; iIndex < m_vDataOutgoing.count(); iIndex++)
    {
        if (m_vDataOutgoing[iIndex].ID() == outgoingData.ID())
        {
            m_vDataOutgoing[iIndex].setData(outgoingData.data());
            m_vDataOutgoing[iIndex].setUpdateTime(QDateTime::currentDateTime());
            return;
        }
    }

    m_vDataOutgoing.append(outgoingData);
    m_vDataOutgoing.last().setUpdateTime(QDateTime::currentDateTime());
}

//-------------------------------------------------------------------------------------------------

void CAirbusDataSupplier::sendData()
{
    foreach (CAirbusDataSupplier* pConsumer, m_vDataOutputs)
    {
        sendDataToConsumer(pConsumer);
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusDataSupplier::sendDataToConsumer(CAirbusDataSupplier* pConsumer)
{
    foreach (CAirbusData data, m_vDataOutgoing)
    {
        pConsumer->receiveData(data);
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusDataSupplier::receiveData(CAirbusData incomingData)
{
    for (int iIndex = 0; iIndex < m_vDataIncoming.count(); iIndex++)
    {
        if (m_vDataIncoming[iIndex].ID() == incomingData.ID() && m_vDataIncoming[iIndex].source() == incomingData.source())
        {
            m_vDataIncoming[iIndex].setData(incomingData.data());
            m_vDataIncoming[iIndex].setUpdateTime(QDateTime::currentDateTime());
            return;
        }
    }

    m_vDataIncoming.append(incomingData);
    m_vDataIncoming.last().setUpdateTime(QDateTime::currentDateTime());
}

//-------------------------------------------------------------------------------------------------

void CAirbusDataSupplier::removeData(EAirbusData eDataID)
{
    for (int iIndex = 0; iIndex < m_vDataIncoming.count(); iIndex++)
    {
        if (m_vDataIncoming[iIndex].ID() == eDataID)
        {
            m_vDataIncoming.remove(iIndex);
            iIndex--;
        }
    }
}
