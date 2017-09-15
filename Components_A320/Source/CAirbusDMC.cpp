
// Qt
#include <QPainter>

// qt-plus
#include "CLogger.h"

// Quick3D
#include "C3DScene.h"

// Application
#include "CAirbusDMC.h"

//-------------------------------------------------------------------------------------------------

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusDMC::instantiator(C3DScene* pScene)
{
    return new CAirbusDMC(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusDMC::CAirbusDMC(C3DScene* pScene)
    : CAirbusFlightComputer(pScene)
    , m_iLastHeight(0)
{
    m_rVelocityBar = QRectF(0.00, 0.20, 0.20, 0.60);
    m_rArtificialHorizon = QRectF(0.25, 0.20, 0.45, 0.60);
    m_rAltitudeBar = QRectF(0.75, 0.20, 0.25, 0.60);
    m_rFMA = QRectF(0.00, 0.00, 1.00, 0.20);

    m_iVerticalSpeedMarker.addValue(-6000.0 * FAC_FPM_TO_MS,  1.00);
    m_iVerticalSpeedMarker.addValue(-2000.0 * FAC_FPM_TO_MS,  0.90);
    m_iVerticalSpeedMarker.addValue(-1500.0 * FAC_FPM_TO_MS,  0.75);
    m_iVerticalSpeedMarker.addValue(-1000.0 * FAC_FPM_TO_MS,  0.60);
    m_iVerticalSpeedMarker.addValue( -500.0 * FAC_FPM_TO_MS,  0.30);
    m_iVerticalSpeedMarker.addValue(    0.0, 0.0);
    m_iVerticalSpeedMarker.addValue(  500.0 * FAC_FPM_TO_MS, -0.30);
    m_iVerticalSpeedMarker.addValue( 1000.0 * FAC_FPM_TO_MS, -0.60);
    m_iVerticalSpeedMarker.addValue( 1500.0 * FAC_FPM_TO_MS, -0.75);
    m_iVerticalSpeedMarker.addValue( 2000.0 * FAC_FPM_TO_MS, -0.90);
    m_iVerticalSpeedMarker.addValue( 6000.0 * FAC_FPM_TO_MS, -1.00);

    m_rCompass = QRectF(0.20, 0.20, 0.60, 0.60);

    m_rEWD_Engines = QRectF(0.00, 0.00, 0.60, 0.70);

    // Thin pens

    m_pAmberThin = QPen(A320_Color_Amber);
    m_pAmberThin.setWidth(2);

    m_pBlueThin = QPen(A320_Color_Blue);
    m_pBlueThin.setWidth(2);

    m_pGreenThin = QPen(A320_Color_Green);
    m_pGreenThin.setWidth(2);

    m_pPurpleThin = QPen(A320_Color_Purple);
    m_pPurpleThin.setWidth(2);

    m_pWhiteThin = QPen(A320_Color_White);
    m_pWhiteThin.setWidth(2);

    m_pYellowThin = QPen(A320_Color_Yellow);
    m_pYellowThin.setWidth(2);

    // Bold pens

    m_pAmberBold = QPen(A320_Color_Amber);
    m_pAmberBold.setWidth(4);

    m_pBlueBold = QPen(A320_Color_Blue);
    m_pBlueBold.setWidth(4);

    m_pGreenBold = QPen(A320_Color_Green);
    m_pGreenBold.setWidth(4);

    m_pPurpleBold = QPen(A320_Color_Purple);
    m_pPurpleBold.setWidth(4);

    m_pWhiteBold = QPen(A320_Color_White);
    m_pWhiteBold.setWidth(4);

    m_pYellowBold = QPen(A320_Color_Yellow);
    m_pYellowBold.setWidth(4);

    QVector<qreal> dashes;
    dashes << 4 << 4;

    m_pWhiteDashed = QPen(A320_Color_White);
    m_pWhiteDashed.setDashPattern(dashes);
}

//-------------------------------------------------------------------------------------------------

CAirbusDMC::~CAirbusDMC()
{
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::update(double dDeltaTime)
{
    CAirbusFlightComputer::update(dDeltaTime);
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::updateTexture(CTexture* pTexture, double dDeltaTime)
{
    QPainter painter;

    if (painter.begin(&(pTexture->image())))
    {
        if (m_iLastHeight != pTexture->image().height())
        {
            m_iLastHeight = pTexture->image().height();
            int iFontLargeSize = ((m_iLastHeight / 16) * 4) / 5;
            int iFontSmallSize = (iFontLargeSize * 4) / 5;
            m_fFontLarge = QFont(A320_MCDU_FONT, iFontLargeSize);
            m_fFontSmall = QFont(A320_MCDU_FONT, iFontSmallSize);
        }

        painter.fillRect(0, 0, pTexture->image().width(), pTexture->image().height(), QColor(0, 0, 0));

        if (m_bPowered)
        {
            if (pTexture->name().contains("_PFD"))
            {
                updateTexture_PFD(&painter, pTexture, dDeltaTime);
            }
            else if (pTexture->name().contains("_ND"))
            {
                updateTexture_ND(&painter, pTexture, dDeltaTime);
            }
            else if (pTexture->name().contains("_EWD"))
            {
                updateTexture_EWD(&painter, pTexture, dDeltaTime);
            }
            else if (pTexture->name().contains("_SD"))
            {
                updateTexture_SD(&painter, pTexture, dDeltaTime);
            }
        }

        painter.end();
    }
}
