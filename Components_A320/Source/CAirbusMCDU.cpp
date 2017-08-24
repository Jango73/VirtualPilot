
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
    , m_ePage(mpMenu)
{
    LOG_DEBUG("CAirbusMCDU::CAirbusMCDU()");
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
    QPainter painter;

    if (painter.begin(&(pTexture->image())))
    {
        painter.fillRect(0, 0, pTexture->image().width(), pTexture->image().height(), QColor(0, 0, 0));

        if (m_bPowered)
        {
            double X = 0.0 * pTexture->image().width();
            double Y = 0.0 * pTexture->image().height();
            double W = 1.0 * pTexture->image().width();
            double H = 1.0 * pTexture->image().height();

            double xCellSize = W / (double) MCDU_W;
            double yCellSize = H / (double) MCDU_H;

            int iFontLargeSize = H / MCDU_H;
            int iFontSmallSize = (iFontLargeSize * 4) / 3;

            QFont fFontLarge = QFont("Arial", iFontLargeSize);
            QFont fFontSmall = QFont("Arial", iFontSmallSize);

            painter.resetTransform();

            // Set main font
            painter.setPen(A320_Color_White);
            painter.setFont(fFontLarge);

            printCurrentPage();

            // painter.drawText(rWholePart, Qt::AlignCenter, "MCDU");

            for (int y = 0; y < MCDU_H; y++)
            {
                for (int x = 0; x < MCDU_H; x++)
                {
                    QString sText(m_aScreen[x][y].m_cChar);
                    int screenX = x * xCellSize;
                    int screenY = y * yCellSize;
                    QRectF rChar(screenX, screenY, xCellSize, yCellSize);
                    painter.drawText(rChar, Qt::AlignCenter, sText);
                }
            }
        }

        painter.end();
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::handleEvent(CQ3DEvent* event)
{
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

void CAirbusMCDU::printData(int iLine, bool bLeft, const QString& sText)
{
    QPoint pWhere(0, 2 + iLine * 2);

    if (bLeft == false)
    {
        pWhere.setX(MCDU_W - sText.length());
    }

    printAt(pWhere, sText, A320_Color_White, true);
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

void CAirbusMCDU::printPage_Menu()
{
    printTitle("MCDU MENU");

    // Left data
    printData(0, true, "<FMGC");
    printData(1, true, "<DATA LINK");
    printData(2, true, "<AIDS");
    printData(3, true, "<CFDS [REQ]");

    // Right data
    printData(5, false, "RETURN>");
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

    // Right data
    printData(4, false, "WIND>");
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printPage_InitB()
{
    printTitle("INIT B");
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printPage_RouteSelection()
{
    // Left data
    printData(5, true, "<RETURN");

    // Right data
    printData(5, false, "INSERT*");
}
