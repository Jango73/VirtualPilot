
// qt-plus
#include "CLogger.h"

// Application
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
    DELETE_VECTOR_ITEMS(m_vRunways);
}

//-------------------------------------------------------------------------------------------------

QVector<CRunway*>& CAirport::runways()
{
    return m_vRunways;
}

//-------------------------------------------------------------------------------------------------

const QVector<CRunway*>& CAirport::runways() const
{
    return m_vRunways;
}

//-------------------------------------------------------------------------------------------------

QMap<ERadioType, double>& CAirport::radios()
{
    return m_mRadios;
}

//-------------------------------------------------------------------------------------------------

const QMap<ERadioType, double>& CAirport::radios() const
{
    return m_mRadios;
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
        QString sType = xRadio.attributes()[ParamName_Type];
        ERadioType eType = rtTower;

        if (sType == ParamName_RadioType_Approach)
            eType = rtApproach;
        else if (sType == ParamName_RadioType_ATIS)
            eType = rtATIS;
        else if (sType == ParamName_RadioType_Departure)
            eType = rtDeparture;
        else if (sType == ParamName_RadioType_Ground)
            eType = rtGround;

        m_mRadios[eType] = xRadio.attributes()[ParamName_Frequency].toDouble();
    }
}

//-------------------------------------------------------------------------------------------------

void CAirport::dump(QTextStream& stream, int iIdent)
{
    dumpIdent(stream, iIdent, QString("[CAirport]"));
    dumpIdent(stream, iIdent, QString("Radios : %1").arg(m_vRunways.count()));
    dumpIdent(stream, iIdent, QString("Runways :"));

    dumpOpenBlock(stream, iIdent); iIdent++;
    foreach (CRunway* pRunway, m_vRunways)
    {
        pRunway->dump(stream, iIdent);
    }
    iIdent--; dumpCloseBlock(stream, iIdent);

    CNavaidComponent::dump(stream, iIdent);
}
