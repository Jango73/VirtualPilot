
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

void CRunway::loadParameters(const QString& sBaseFile, const CXMLNode& xRunway)
{
    CNavaidComponent::loadParameters(sBaseFile, xRunway);

    m_vSize.X = xRunway.attributes()[ParamName_Width].toDouble();
    m_vSize.Z = xRunway.attributes()[ParamName_Length].toDouble();

    m_vRotation.Y = xRunway.attributes()[ParamName_Heading].toDouble();
}

//-------------------------------------------------------------------------------------------------

void CRunway::dump(QTextStream& stream, int iIdent)
{
    dumpIdent(stream, iIdent, QString("[CRunway]"));
    dumpIdent(stream, iIdent, QString("Size : %1").arg(m_vSize.toString()));
    dumpIdent(stream, iIdent, QString("Rotation : %1").arg(m_vRotation.toString()));

    CNavaidComponent::dump(stream, iIdent);
}
