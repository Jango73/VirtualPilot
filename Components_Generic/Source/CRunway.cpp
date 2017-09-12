
#include "CRunway.h"

//-------------------------------------------------------------------------------------------------

using namespace Math;

//-------------------------------------------------------------------------------------------------

CRunway::CRunway()
{
}

//-------------------------------------------------------------------------------------------------

CRunway::~CRunway()
{
}

//-------------------------------------------------------------------------------------------------

Math::CVector3 CRunway::size() const
{
    return m_vSize;
}

//-------------------------------------------------------------------------------------------------

Math::CVector3 CRunway::rotation() const
{
    return m_vRotation;
}

//-------------------------------------------------------------------------------------------------

void CRunway::loadParameters(const QString& sBaseFile, CXMLNode xRunway)
{
    CNavaidComponent::loadParameters(sBaseFile, xRunway);

    m_vSize.X = xRunway.attributes()[ParamName_Width].toDouble();
    m_vSize.Z = xRunway.attributes()[ParamName_Length].toDouble();

    m_vRotation.Y = xRunway.attributes()[ParamName_Heading].toDouble();
}
