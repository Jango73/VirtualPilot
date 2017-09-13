
#include "CNavaid.h"

//-------------------------------------------------------------------------------------------------

using namespace Math;

//-------------------------------------------------------------------------------------------------

CNavaid::CNavaid()
    : m_dFrequency_MHz(0.0)
    , m_eType(ntNone)
    , m_eILSType(ilstNone)
{
}

//-------------------------------------------------------------------------------------------------

CNavaid::~CNavaid()
{
}

//-------------------------------------------------------------------------------------------------

double CNavaid::frequency_MHz() const
{
    return m_dFrequency_MHz;
}

//-------------------------------------------------------------------------------------------------

ENavaidType CNavaid::type() const
{
    return m_eType;
}

//-------------------------------------------------------------------------------------------------

EILSType CNavaid::ILSType() const
{
    return m_eILSType;
}

//-------------------------------------------------------------------------------------------------

void CNavaid::loadParameters(const QString& sBaseFile, CXMLNode xNavaid)
{
    CNavaidComponent::loadParameters(sBaseFile, xNavaid);

    QString sType = xNavaid.attributes()[ParamName_Type];

    if (sType == ParamName_NavaidType_ILS)
        m_eType = ntILS;
    else if (sType == ParamName_NavaidType_NDB)
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

    if (m_eType == ntILS)
    {
        QString sILSType = xNavaid.attributes()[ParamName_ILSType];

        if (sILSType == ParamName_ILSType_Cat1)
            m_eILSType = ilstCat1;
        else if (sILSType == ParamName_ILSType_Cat2)
            m_eILSType = ilstCat2;
        else if (sILSType == ParamName_ILSType_Cat3)
            m_eILSType = ilstCat3;
    }
}

//-------------------------------------------------------------------------------------------------

void CNavaid::dump(QTextStream& stream, int iIdent)
{
    dumpIdent(stream, iIdent, QString("[CNavaid]"));
    dumpIdent(stream, iIdent, QString("Type : %1").arg(m_eType));
    dumpIdent(stream, iIdent, QString("Frequency : %1").arg(m_dFrequency_MHz));

    CNavaidComponent::dump(stream, iIdent);
}
