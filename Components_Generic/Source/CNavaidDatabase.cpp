
// qt-plus
#include "CLogger.h"

// Application
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
    LOG_DEBUG("CNavaidDatabase::CNavaidDatabase()");
}

//-------------------------------------------------------------------------------------------------

CNavaidDatabase::~CNavaidDatabase()
{
    LOG_DEBUG("CNavaidDatabase::~CNavaidDatabase()");

    DELETE_VECTOR_ITEMS(m_vNavaids);
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
        append(pNewAiport->geoloc(), pNewAiport);
    }

    // Load navaids
    QVector<CXMLNode> xNavaids = xDataBase.getNodesByTagName(ParamName_Navaid);

    foreach (CXMLNode xNavaid, xNavaids)
    {
        CNavaid* pNavaid = new CNavaid();
        pNavaid->loadParameters(sFileName, xNavaid);
        m_vNavaids << pNavaid;
        append(pNavaid->geoloc(), pNavaid);
    }
}
