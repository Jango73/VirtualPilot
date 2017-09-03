
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

CComponent* CAirbusDMC::instanciator(C3DScene* pScene)
{
    return new CAirbusDMC(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusDMC::CAirbusDMC(C3DScene* pScene)
    : CAirbusFlightComputer(pScene)
{
    LOG_DEBUG("CAirbusDMC::CAirbusDMC()");

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

    m_pGreenBold = QPen(A320_Color_Green);
    m_pGreenBold.setWidth(2);

    m_pYellowBold = QPen(A320_Color_Yellow);
    m_pYellowBold.setWidth(2);

    QVector<qreal> dashes;
    dashes << 4 << 4;

    m_pWhiteDashed = QPen(A320_Color_White);
    m_pWhiteDashed.setDashPattern(dashes);
}

//-------------------------------------------------------------------------------------------------

CAirbusDMC::~CAirbusDMC()
{
    LOG_DEBUG("CAirbusDMC::~CAirbusDMC()");
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
        int iFontLargeSize = ((pTexture->image().height() / 16) * 4) / 5;

        m_fMainFont = QFont(A320_MCDU_FONT, iFontLargeSize);

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
