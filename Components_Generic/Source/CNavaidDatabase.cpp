
#include "CNavaidDatabase.h"

//-------------------------------------------------------------------------------------------------

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CNavaidDatabase::instantiator(C3DScene* pScene)
{
    return new CNavaidDatabase(pScene);
}

//-------------------------------------------------------------------------------------------------

CNavaidDatabase::CNavaidDatabase(C3DScene* pScene)
    : CComponent(pScene)
{
}

//-------------------------------------------------------------------------------------------------

CNavaidDatabase::~CNavaidDatabase()
{
    foreach (CNavaidComponent* pNavaid, m_vNavaids)
    {
        delete pNavaid;
    }
}

//-------------------------------------------------------------------------------------------------

void CNavaidDatabase::loadParameters(const QString& sBaseFile, CXMLNode xComponent)
{
    CComponent::loadParameters(sBaseFile, xComponent);

    QString sFileName = xComponent.attributes()[ParamName_File];

    if (sFileName.isEmpty() == false)
    {
        loadFromFile(sFileName);
    }
}

//-------------------------------------------------------------------------------------------------

void CNavaidDatabase::loadFromFile(const QString& sFileName)
{
    CXMLNode xDataBase = CXMLNode::loadXMLFromFile(sFileName);

    // Load airports
    QVector<CXMLNode> xAirports = xDataBase.getNodesByTagName(ParamName_Airport);

    foreach (CXMLNode xAirport, xAirports)
    {
        CAirport* pNewAiport = new CAirport();
        pNewAiport->loadParameters(sFileName, xAirport);
        m_vNavaids << pNewAiport;
    }
}
