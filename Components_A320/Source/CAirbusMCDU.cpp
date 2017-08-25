
// Qt
#include <QPainter>

// qt-plus
#include "CLogger.h"

// Quick3D
#include "C3DScene.h"

// Application
#include "CAirbusMCDU.h"

//-------------------------------------------------------------------------------------------------

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusMCDU::instanciator(C3DScene* pScene)
{
    return new CAirbusMCDU(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusMCDU::CAirbusMCDU(C3DScene* pScene)
    : CAirbusFlightComputer(pScene)
    , m_ePage(mpInitA)
    , m_iSubPage(0)
    , m_bNeedScreenRefresh(true)
{
    LOG_DEBUG("CAirbusMCDU::CAirbusMCDU()");

    m_mEventToKey[EventName_MCDU_CAPT_1L] = mk1L;
    m_mEventToKey[EventName_MCDU_CAPT_2L] = mk2L;
    m_mEventToKey[EventName_MCDU_CAPT_3L] = mk3L;
    m_mEventToKey[EventName_MCDU_CAPT_4L] = mk4L;
    m_mEventToKey[EventName_MCDU_CAPT_5L] = mk5L;
    m_mEventToKey[EventName_MCDU_CAPT_6L] = mk6L;
    m_mEventToKey[EventName_MCDU_CAPT_1R] = mk1R;
    m_mEventToKey[EventName_MCDU_CAPT_2R] = mk2R;
    m_mEventToKey[EventName_MCDU_CAPT_3R] = mk3R;
    m_mEventToKey[EventName_MCDU_CAPT_4R] = mk4R;
    m_mEventToKey[EventName_MCDU_CAPT_5R] = mk5R;
    m_mEventToKey[EventName_MCDU_CAPT_6R] = mk6R;
    m_mEventToKey[EventName_MCDU_CAPT_INIT] = mkInit;
    m_mEventToKey[EventName_MCDU_CAPT_MENU] = mkMenu;
    m_mEventToKey[EventName_MCDU_CAPT_0] = mk0;
    m_mEventToKey[EventName_MCDU_CAPT_1] = mk1;
    m_mEventToKey[EventName_MCDU_CAPT_2] = mk2;
    m_mEventToKey[EventName_MCDU_CAPT_3] = mk3;
    m_mEventToKey[EventName_MCDU_CAPT_4] = mk4;
    m_mEventToKey[EventName_MCDU_CAPT_5] = mk5;
    m_mEventToKey[EventName_MCDU_CAPT_6] = mk6;
    m_mEventToKey[EventName_MCDU_CAPT_7] = mk7;
    m_mEventToKey[EventName_MCDU_CAPT_8] = mk8;
    m_mEventToKey[EventName_MCDU_CAPT_9] = mk9;

    m_mEventToKey[EventName_MCDU_FO_1L] = mk1L;
    m_mEventToKey[EventName_MCDU_FO_2L] = mk2L;
    m_mEventToKey[EventName_MCDU_FO_3L] = mk3L;
    m_mEventToKey[EventName_MCDU_FO_4L] = mk4L;
    m_mEventToKey[EventName_MCDU_FO_5L] = mk5L;
    m_mEventToKey[EventName_MCDU_FO_6L] = mk6L;
    m_mEventToKey[EventName_MCDU_FO_1R] = mk1R;
    m_mEventToKey[EventName_MCDU_FO_2R] = mk2R;
    m_mEventToKey[EventName_MCDU_FO_3R] = mk3R;
    m_mEventToKey[EventName_MCDU_FO_4R] = mk4R;
    m_mEventToKey[EventName_MCDU_FO_5R] = mk5R;
    m_mEventToKey[EventName_MCDU_FO_6R] = mk6R;
    m_mEventToKey[EventName_MCDU_FO_INIT] = mkInit;
    m_mEventToKey[EventName_MCDU_FO_MENU] = mkMenu;
    m_mEventToKey[EventName_MCDU_FO_0] = mk0;
    m_mEventToKey[EventName_MCDU_FO_1] = mk1;
    m_mEventToKey[EventName_MCDU_FO_2] = mk2;
    m_mEventToKey[EventName_MCDU_FO_3] = mk3;
    m_mEventToKey[EventName_MCDU_FO_4] = mk4;
    m_mEventToKey[EventName_MCDU_FO_5] = mk5;
    m_mEventToKey[EventName_MCDU_FO_6] = mk6;
    m_mEventToKey[EventName_MCDU_FO_7] = mk7;
    m_mEventToKey[EventName_MCDU_FO_8] = mk8;
    m_mEventToKey[EventName_MCDU_FO_9] = mk9;
}

//-------------------------------------------------------------------------------------------------

CAirbusMCDU::~CAirbusMCDU()
{
    LOG_DEBUG("CAirbusMCDU::~CAirbusMCDU()");
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::update(double dDeltaTime)
{
    CAirbusFlightComputer::update(dDeltaTime);
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::updateTexture(CTexture* pTexture, double dDeltaTime)
{
    if (m_bNeedScreenRefresh)
    {
        m_bNeedScreenRefresh = false;

        QPainter painter;

        if (painter.begin(&(pTexture->image())))
        {
            painter.fillRect(0, 0, pTexture->image().width(), pTexture->image().height(), QColor(0, 0, 0));

            if (m_bPowered)
            {
                double W = 1.0 * pTexture->image().width();
                double H = 1.0 * pTexture->image().height();

                double xCellSize = W / (double) MCDU_W;
                double yCellSize = H / (double) MCDU_H;

                int iFontLargeSize = ((H / MCDU_H) * 4) / 5;
                int iFontSmallSize = (iFontLargeSize * 4) / 5;

                QFont fFontLarge = QFont("Arial", iFontLargeSize);
                QFont fFontSmall = QFont("Arial", iFontSmallSize);

                painter.resetTransform();

                for (int y = 0; y < MCDU_H; y++)
                {
                    for (int x = 0; x < MCDU_W; x++)
                    {
                        m_aScreen[x][y].m_cChar = ' ';
                    }
                }

                printCurrentPage();
                printScratchPad();

                for (int y = 0; y < MCDU_H; y++)
                {
                    for (int x = 0; x < MCDU_W; x++)
                    {
                        if (m_aScreen[x][y].m_bLarge)
                            painter.setFont(fFontLarge);
                        else
                            painter.setFont(fFontSmall);

                        painter.setPen(m_aScreen[x][y].m_cColor);

                        int screenX = x * xCellSize;
                        int screenY = y * yCellSize;
                        QRectF rChar(screenX, screenY, xCellSize, yCellSize);

                        painter.drawText(rChar, Qt::AlignCenter, QString(m_aScreen[x][y].m_cChar));
                    }
                }
            }

            painter.end();
        }
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::handleEvent(CQ3DEvent* event)
{
    if (m_mEventToKey.contains(event->getName()) && event->getAction() == CQ3DEvent::Press)
    {
        handleKey(m_mEventToKey[event->getName()]);
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::handleKey(EMCDUKey eKey)
{
    if (eKey >= mkSpace && eKey <= mkZ)
    {
        if (m_sScratchPad.count() < MCDU_W)
        {
            m_sScratchPad += QString(QChar(eKey));
        }
    }
    else if (eKey >= mk1L && eKey <= mk6R)
    {
        switch (m_ePage)
        {
        case mpMenu: handleKey_Menu(eKey); break;
        case mpInitA: handleKey_InitA(eKey); break;
        case mpInitB: handleKey_InitB(eKey); break;
        case mpRouteSelection: handleKey_RouteSelection(eKey); break;
        case mpFlightPlanA: handleKey_FlightPlanA(eKey); break;
        }
    }
    else if (eKey == mkInit)
    {
        m_ePage = mpInitA;
    }
    else if (eKey == mkMenu)
    {
        m_ePage = mpMenu;
    }
    else if (eKey == mkClear)
    {
        m_sScratchPad = MCDU_CLEAR;
    }

    m_bNeedScreenRefresh = true;
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printAt(QPoint pWhere, const QString& sText, QColor cColor, bool bLarge)
{
    for (int index = 0; index < sText.length(); index++)
    {
        int x = pWhere.x() + index;
        int y = pWhere.y();

        if (x >= 0 && x < MCDU_W && y >= 0 && y < MCDU_H)
        {
            m_aScreen[x][y].m_cChar = sText[index];
            m_aScreen[x][y].m_cColor = cColor;
            m_aScreen[x][y].m_bLarge = bLarge;
        }
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printCenteredAt(QPoint pWhere, const QString& sText, QColor cColor, bool bLarge)
{
    int halfLength = sText.length() / 2;
    QPoint newPos(pWhere.x() - halfLength, pWhere.y());
    printAt(newPos, sText, cColor, bLarge);
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printTitle(const QString& sText)
{
    printCenteredAt(QPoint(MCDU_W / 2, 0), sText, A320_Color_White, true);
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printLeftTitle(const QString& sText)
{
    printAt(QPoint(0, 0), sText, A320_Color_White, false);
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printLabel(int iLine, bool bLeft, const QString& sText)
{
    QPoint pWhere(0, 1 + iLine * 2);

    if (bLeft == false)
    {
        pWhere.setX(MCDU_W - sText.length());
    }

    printAt(pWhere, sText, A320_Color_White, false);
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printData(int iLine, bool bLeft, const QString& sText, QColor cColor)
{
    QPoint pWhere(0, 2 + iLine * 2);

    if (bLeft == false)
    {
        pWhere.setX(MCDU_W - sText.length());
    }

    printAt(pWhere, sText, cColor, true);
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printCurrentPage()
{
    switch (m_ePage)
    {
    case mpMenu: printPage_Menu(); break;
    case mpInitA: printPage_InitA(); break;
    case mpInitB: printPage_InitB(); break;
    case mpRouteSelection: printPage_RouteSelection(); break;
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printScratchPad()
{
    printAt(QPoint(0, MCDU_H - 1), m_sScratchPad, A320_Color_White, true);
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printPage_Menu()
{
    printTitle("MCDU MENU");

    // Left data
    printData(0, true, "<FMGC");
    printData(1, true, "<DATA LINK");
    printData(2, true, "<AIDS");
    printData(3, true, "<CFDS");

    // Right data
    printData(5, false, "RETURN>");
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::handleKey_Menu(EMCDUKey eKey)
{
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printPage_InitA()
{
    printTitle("INIT");

    // Left labels
    printLabel(0, true, "CO RTE");
    printLabel(1, true, "ALTN/CO RTE");
    printLabel(2, true, "FLT NBR");
    printLabel(3, true, "LAT");
    printLabel(4, true, "COST INDEX");
    printLabel(5, true, "CRZ FL/TEMP");

    // Right labels
    printLabel(0, false, "FROM/TO  ");
    printLabel(1, false, "INIT ");
    printLabel(3, false, "LONG");
    printLabel(5, false, "TROPO");

    // Get data
    QString sFM_CompanyRoute = GETDATA_STRING(adFM_CompanyRoute);
    QString sFM_FlightNumber = GETDATA_STRING(adFM_FlightNumber);
    QString sFM_ICAOFrom = GETDATA_STRING(adFM_ICAOFrom);
    QString sFM_ICAOTo = GETDATA_STRING(adFM_ICAOTo);

    QString sFromTo = QString("%1/%2").arg(sFM_ICAOFrom).arg(sFM_ICAOTo);

    // Left data
    printData(0, true, sFM_CompanyRoute.isEmpty() == false ? sFM_CompanyRoute : FORMAT_COMPANY_ROUTE, A320_Color_Blue);
    printData(2, true, sFM_FlightNumber.isEmpty() == false ? sFM_FlightNumber : FORMAT_COMPANY_ROUTE, A320_Color_Blue);

    // Right data
    printData(0, false, sFM_ICAOFrom.isEmpty() == false ? sFromTo : FORMAT_ICAO_FROM_TO, A320_Color_Blue);
    printData(1, false, "REQUEST*");
    printData(2, false, "ALIGN IRS>");
    printData(4, false, "WIND>");
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::handleKey_InitA(EMCDUKey eKey)
{
    switch (eKey)
    {
    case mk1L:
        if (m_sScratchPad.isEmpty() == false)
        {
            sendData(mdsCompanyRoute, m_sScratchPad);
            m_sScratchPad.clear();
        }
        break;
    case mk1R:
        if (m_sScratchPad.isEmpty() == false)
        {
            if (respectsFormat(m_sScratchPad, FORMAT_ICAO_FROM_TO))
            {
                sendData(mdsICAOFromTo, m_sScratchPad);
            }
        }
        break;
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printPage_InitB()
{
    printTitle("INIT B");
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::handleKey_InitB(EMCDUKey eKey)
{
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printPage_RouteSelection()
{
    // Left data
    printData(5, true, "<RETURN");

    // Right data
    printData(5, false, "INSERT*");
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::handleKey_RouteSelection(EMCDUKey eKey)
{
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printPage_FlightPlanA()
{
    CAirbusFlightPlan* pFG_FlightPlan_ptr = GETDATA_POINTER(adFG_FlightPlan_ptr, CAirbusFlightPlan);

    printLeftTitle(" FROM");
    printLabel(0, true, TEXT_FPLN_HEADER);

    if (pFG_FlightPlan_ptr != nullptr)
    {
        int iFirstWaypoint = m_iSubPage * FPLN_WAYP_PER_PAGE;
        int iLine = 0;

        for (int index = iFirstWaypoint; index < pFG_FlightPlan_ptr->waypoints().count(); index++, iLine++)
        {
            QString sName = pFG_FlightPlan_ptr->waypoints()[index].name();
            QString sSpeed = printableSpeed(pFG_FlightPlan_ptr->waypoints()[index].computedSpeed_ms());
            QString sAltitude = printableAltitude(pFG_FlightPlan_ptr->waypoints()[index].computedAltitude_m());
            QString sSpdAlt = QString("%1/ %2").arg(sSpeed).arg(sAltitude);

            printData(iLine, true, sName, A320_Color_Blue);
            printData(iLine, false, sSpdAlt, A320_Color_Blue);
        }
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::handleKey_FlightPlanA(EMCDUKey eKey)
{
}

//-------------------------------------------------------------------------------------------------

QString CAirbusMCDU::printableAltitude(double dAltitude_m)
{
    double dAltitude_ft = dAltitude_m * FAC_METERS_TO_FEET;

    if (dAltitude_ft < 10000.0)
    {
        return QString::number(dAltitude_ft, 'g', 0);
    }

    return QString("FL").arg((int) (dAltitude_ft / 100.0));
}


//-------------------------------------------------------------------------------------------------

QString CAirbusMCDU::printableSpeed(double dSpeed_ms)
{
    double dSpeed_kt = dSpeed_ms * FAC_MS_TO_KNOTS;
    return QString::number(dSpeed_kt, 'g', 0);
}

//-------------------------------------------------------------------------------------------------

bool CAirbusMCDU::respectsFormat(const QString& sValue, const QString& sFormat)
{
    // TODO : check if sValue respects sFormat
    return true;
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::sendData(EMCDUDataSet eDataName, QVariant vValue)
{
    pushData(CAirbusData(m_sName, adMCDU_DataSetName, (int) eDataName, false));
    pushData(CAirbusData(m_sName, adMCDU_DataSetValue, vValue, false));
}
