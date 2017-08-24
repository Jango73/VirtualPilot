
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

void CAirbusDMC::updateTexture_EWD(QPainter* pPainter, CTexture* pTexture, double dDeltaTime)
{
    double dFADEC_Engine1_N1_norm = GETDATA_DOUBLE(adFADEC_Engine1_N1_norm);
    double dFADEC_Engine2_N1_norm = GETDATA_DOUBLE(adFADEC_Engine2_N1_norm);

    // Compute coordinates
    double X = m_rEWD_Engines.left() * pTexture->image().width();
    double Y = m_rEWD_Engines.top() * pTexture->image().height();
    double W = m_rEWD_Engines.width() * pTexture->image().width();
    // double H = m_rEWD_Engines.height() * pTexture->getImage().height();
    double W25 = W / 2.50;
    // double W4 = W / 4.00;
    // double H2 = H * 0.50;
    // double dAltitudeScale = 4.0;

    QRectF rEngine1_N1(X, Y, W25, W25);
    QRectF rEngine2_N1((X + W) - W25, Y, W25, W25);

    drawEngineN1Gauge(pPainter, pTexture, dDeltaTime, rEngine1_N1, dFADEC_Engine1_N1_norm);
    drawEngineN1Gauge(pPainter, pTexture, dDeltaTime, rEngine2_N1, dFADEC_Engine2_N1_norm);
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::drawEngineN1Gauge(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, const QRectF& rRect, double dN1)
{
    double dAngle1 = 10;
    double dAngle2 = 200;
    double dAngle_N1 = (dN1 * (dAngle2 - dAngle1)) + 60;

    // Set main font
    pPainter->setFont(m_fMainFont);

    pPainter->resetTransform();

    pPainter->setPen(A320_Color_White);
    pPainter->drawArc(rRect, (int) dAngle1 * 16, (int) dAngle2 * 16);

    pPainter->translate(rRect.center());
    pPainter->rotate(dAngle_N1);

    pPainter->setPen(m_pGreenBold);
    pPainter->drawLine(0.0, 0.0, 0.0, rRect.height() * 0.5);

    pPainter->resetTransform();

    // double X = rRect.left();
    // double Y = rRect.top();
    double W = rRect.width();
    double H = rRect.height();
    double W15 = W / 2.80;
    double H4 = H / 4.00;

    QRectF rText(rRect.center().x() - W15, rRect.center().y(), W15 * 2.0, H4);

    pPainter->fillRect(rText, QColor(0, 0, 0));

    pPainter->drawText(rText, Qt::AlignCenter, QString::number(dN1 * 100.0, 'f', 1));

    pPainter->setPen(A320_Color_Green);
    pPainter->drawRect(rText);
    pPainter->drawRect(rText.adjusted(2, 2, -2, -2));
}
