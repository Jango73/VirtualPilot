
#include "CNavaidComponent.h"

//-------------------------------------------------------------------------------------------------

using namespace Math;

//-------------------------------------------------------------------------------------------------

CNavaidComponent::CNavaidComponent()
{
}

//-------------------------------------------------------------------------------------------------

CNavaidComponent::~CNavaidComponent()
{
}


//-------------------------------------------------------------------------------------------------

QString CNavaidComponent::ID() const
{
    return m_sID;
}

//-------------------------------------------------------------------------------------------------

void CNavaidComponent::loadParameters(const QString& sBaseFile, const CXMLNode& xComponent)
{
    m_sID = xComponent.attributes()[ParamName_ID];

    CXMLNode xGeoloc = xComponent.getNodeByTagName(ParamName_Geoloc);

    setGeoloc(CGeoloc(
                  xGeoloc.attributes()[ParamName_Latitude].toDouble(),
                  xGeoloc.attributes()[ParamName_Longitude].toDouble(),
                  xGeoloc.attributes()[ParamName_Altitude].toDouble()
                  ));
}

//-------------------------------------------------------------------------------------------------

/*!
    Dumps this component to \a stream using the indentation value in \a iIdent.
*/
void CNavaidComponent::dump(QTextStream& stream, int iIdent)
{
    dumpIndented(stream, iIdent, QString("[CNavaidComponent]"));
    dumpIndented(stream, iIdent, QString("ID : %1").arg(m_sID));
    dumpIndented(stream, iIdent, QString("Geoloc : %1").arg(geoloc().toString()));
}
