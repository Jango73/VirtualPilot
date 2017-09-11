
#include "CAirport.h"

//-------------------------------------------------------------------------------------------------

using namespace Math;

//-------------------------------------------------------------------------------------------------

CAirport::CAirport()
{
}

//-------------------------------------------------------------------------------------------------

CAirport::~CAirport()
{
    foreach (CRunway* pRunway, m_vRunways)
    {
        delete pRunway;
    }
}

//-------------------------------------------------------------------------------------------------

void CAirport::loadParameters(const QString& sBaseFile, CXMLNode xAirport)
{
    CNavaidComponent::loadParameters(sBaseFile, xAirport);

    QVector<CXMLNode> xRunways = xAirport.getNodesByTagName(ParamName_Runway);

    foreach (CXMLNode xRunway, xRunways)
    {
        CRunway* pRunway = new CRunway();
        pRunway->loadParameters(sBaseFile, xRunway);
        m_vRunways << pRunway;
    }

    QVector<CXMLNode> xRadios = xAirport.getNodesByTagName(ParamName_Radio);

    foreach (CXMLNode xRadio, xRadios)
    {
    }
}
