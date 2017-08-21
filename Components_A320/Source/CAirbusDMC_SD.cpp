
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

void CAirbusDMC::updateTexture_SD(QPainter* pPainter, CTexture* pTexture, double dDeltaTime)
{
    double X = 0.0 * pTexture->image().width();
    double Y = 0.0 * pTexture->image().height();
    double W = 1.0 * pTexture->image().width();
    double H = 1.0 * pTexture->image().height();

    QRectF rWholePart(X, Y, W, H);

    pPainter->resetTransform();

    // Set main font
    pPainter->setPen(A320_Color_White);
    pPainter->setFont(m_fMainFont);

    pPainter->drawText(rWholePart, Qt::AlignCenter, "SD");
}
