
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
