
#include "CNavaid.h"

//-------------------------------------------------------------------------------------------------

using namespace Math;

//-------------------------------------------------------------------------------------------------

CNavaid::CNavaid()
    : m_eType(ntNone)
    , m_dFrequency_MHz(0.0)
{
}

//-------------------------------------------------------------------------------------------------

CNavaid::~CNavaid()
{
}

//-------------------------------------------------------------------------------------------------

void CNavaid::loadParameters(const QString& sBaseFile, CXMLNode xNavaid)
{
    CNavaidComponent::loadParameters(sBaseFile, xNavaid);

    QString sType = xNavaid.attributes()[ParamName_Type];

    if (sType == ParamName_NavaidType_NDB)
        m_eType = ntNDB;
    else if (sType == ParamName_NavaidType_TACAN)
        m_eType = ntTACAN;
    else if (sType == ParamName_NavaidType_VOR)
        m_eType = ntVOR;
    else if (sType == ParamName_NavaidType_VORDME)
        m_eType = ntVORDME;
    else if (sType == ParamName_NavaidType_VORTAC)
        m_eType = ntVORTAC;

    m_dFrequency_MHz = xNavaid.attributes()[ParamName_Frequency].toDouble();
}
