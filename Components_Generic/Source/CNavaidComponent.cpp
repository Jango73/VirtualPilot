
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

CGeoloc CNavaidComponent::geoloc() const
{
    return m_gGeoloc;
}

//-------------------------------------------------------------------------------------------------

void CNavaidComponent::loadParameters(const QString& sBaseFile, CXMLNode xComponent)
{
    m_sID = xComponent.attributes()[ParamName_ID];

    CXMLNode xGeoloc = xComponent.getNodeByTagName(ParamName_Geoloc);

    m_gGeoloc = CGeoloc(
                  xGeoloc.attributes()[ParamName_Latitude].toDouble(),
                  xGeoloc.attributes()[ParamName_Longitude].toDouble(),
                  xGeoloc.attributes()[ParamName_Altitude].toDouble()
                  );
}

//-------------------------------------------------------------------------------------------------

/*!
    Dumps this component to \a stream using the indentation value in \a iIdent.
*/
void CNavaidComponent::dump(QTextStream& stream, int iIdent)
{
    dumpIdent(stream, iIdent, QString("[CNavaidComponent]"));
    dumpIdent(stream, iIdent, QString("ID : %1").arg(m_sID));
    dumpIdent(stream, iIdent, QString("Geoloc : %1").arg(m_gGeoloc.toString()));
}
