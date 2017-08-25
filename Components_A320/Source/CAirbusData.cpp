
// qt-plus
#include "CLogger.h"

// Application
#include "CAirbusData.h"

//-------------------------------------------------------------------------------------------------

CAirbusData::CAirbusData()
    : m_eID(adNone)
    , m_dUpdateTime(QDateTime::currentDateTime())
    , m_bContinuous(true)
{
}

//-------------------------------------------------------------------------------------------------

CAirbusData::CAirbusData(const QString& sSource, EAirbusData eID, QVariant vData, bool bContinuous)
    : m_sSource(sSource)
    , m_eID(eID)
    , m_dUpdateTime(QDateTime::currentDateTime())
    , m_vData(vData)
    , m_bContinuous(bContinuous)
{
}

//-------------------------------------------------------------------------------------------------

CAirbusData::~CAirbusData()
{
}

//-------------------------------------------------------------------------------------------------

bool CAirbusData::valid() const
{
    if (m_bContinuous)
    {
        if (m_dUpdateTime.secsTo(QDateTime::currentDateTime()) > 1)
        {
            return false;
        }
    }

    return true;
}
