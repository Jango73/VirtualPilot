
#include "CRunway.h"

//-------------------------------------------------------------------------------------------------

using namespace Math;

//-------------------------------------------------------------------------------------------------

CRunway::CRunway()
    : m_dHeading_deg(0.0)
{
}

//-------------------------------------------------------------------------------------------------

CRunway::~CRunway()
{
}

//-------------------------------------------------------------------------------------------------

double CRunway::heading_deg() const
{
    return m_dHeading_deg;
}

//-------------------------------------------------------------------------------------------------

Math::CVector3 CRunway::size() const
{
    return m_vSize;
}

//-------------------------------------------------------------------------------------------------

void CRunway::loadParameters(const QString& sBaseFile, CXMLNode xRunway)
{
    CNavaidComponent::loadParameters(sBaseFile, xRunway);

    m_vSize.X = xRunway.attributes()[ParamName_Width].toDouble();
    m_vSize.Z = xRunway.attributes()[ParamName_Length].toDouble();
}
