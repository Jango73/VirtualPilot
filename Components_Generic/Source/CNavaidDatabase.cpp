
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

//-------------------------------------------------------------------------------------------------

void CNavaidDatabase::dump(QTextStream& stream, int iIdent)
{
    dumpIdent(stream, iIdent, QString("[CNavaidDatabase]"));
    dumpIdent(stream, iIdent, QString("Navaids :"));

    dumpOpenBlock(stream, iIdent); iIdent++;
    foreach (CNavaidComponent* pNavaidComponent, m_vNavaids)
    {
        dumpIdent(stream, iIdent, QString("[CNavaid]"));
        dumpIdent(stream, iIdent, QString("ID : %1").arg(pNavaidComponent->ID()));

        CAirport* pAirport = dynamic_cast<CAirport*>(pNavaidComponent);
        if (pAirport != nullptr)
        {
            dumpIdent(stream, iIdent, QString("[CAirport]"));
            dumpIdent(stream, iIdent, QString("Runways : %1").arg(pAirport->runways().count()));
            dumpIdent(stream, iIdent, QString("Radios : %1").arg(pAirport->radios().count()));
        }

        CNavaid* pNavaid = dynamic_cast<CNavaid*>(pNavaidComponent);
        if (pNavaid != nullptr)
        {
            dumpIdent(stream, iIdent, QString("[CNavaid]"));
            dumpIdent(stream, iIdent, QString("Type : %1").arg(pNavaid->type()));
            dumpIdent(stream, iIdent, QString("Frequency : %1").arg(pNavaid->frequency_MHz()));
        }
    }
    iIdent--; dumpCloseBlock(stream, iIdent);

    CComponent::dump(stream, iIdent);
}
