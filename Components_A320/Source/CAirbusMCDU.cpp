
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
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusMCDU::printPage_Menu()
{
    printTitle("MCDU MENU");
    printData(0, true, "<FMGC");
    printData(1, true, "<DATA LINK");
    printData(2, true, "<AIDS");
    printData(3, true, "<CFDS [REQ]");
    printData(5, false, "RETURN>");
}
