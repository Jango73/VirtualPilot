
// qt-plus
#include "CLogger.h"

// Quick3D
#include "C3DScene.h"

// Application
#include "CAirbusDataSupplier.h"

//-------------------------------------------------------------------------------------------------

CAirbusDataSupplier::CAirbusDataSupplier()
{
    LOG_DEBUG("CAirbusDataSupplier::CAirbusDataSupplier()");
}

//-------------------------------------------------------------------------------------------------

CAirbusDataSupplier::~CAirbusDataSupplier()
{
    LOG_DEBUG("CAirbusDataSupplier::~CAirbusDataSupplier()");
}

//-------------------------------------------------------------------------------------------------

CAirbusData* CAirbusDataSupplier::data(EAirbusData eID)
{
    for (int iIndex = 0; iIndex < m_vData.count(); iIndex++)
    {
        if (m_vData[iIndex].ID() == eID)
        {
            return &(m_vData[iIndex]);
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

void CAirbusDataSupplier::pushData(CAirbusData incomingData)
{
    for (int iIndex = 0; iIndex < m_vData.count(); iIndex++)
    {
        if (m_vData[iIndex].ID() == incomingData.ID() && m_vData[iIndex].source() == incomingData.source())
        {
            m_vData[iIndex].setData(incomingData.data());
            return;
        }
    }

    m_vData.append(incomingData);
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
    foreach (CAirbusData data, m_vData)
    {
        pConsumer->receiveData(data);
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusDataSupplier::receiveData(CAirbusData incomingData)
{
    for (int iIndex = 0; iIndex < m_vData.count(); iIndex++)
    {
        if (m_vData[iIndex].ID() == incomingData.ID() && m_vData[iIndex].source() == incomingData.source())
        {
            m_vData[iIndex].setData(incomingData.data());
            m_vData[iIndex].setUpdateTime(QDateTime::currentDateTime());
            return;
        }
    }

    m_vData.append(incomingData);
    m_vData.last().setUpdateTime(QDateTime::currentDateTime());
}

//-------------------------------------------------------------------------------------------------

void CAirbusDataSupplier::removeData(EAirbusData eDataID)
{
    for (int iIndex = 0; iIndex < m_vData.count(); iIndex++)
    {
        if (m_vData[iIndex].ID() == eDataID)
        {
            m_vData.remove(iIndex);
            iIndex--;
        }
    }
}
