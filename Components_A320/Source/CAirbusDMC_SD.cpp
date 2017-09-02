
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
    pPainter->resetTransform();

    pPainter->fillRect(0, 0, pTexture->image().width(), pTexture->image().height(), QColor(0, 0, 0));

    drawElectricalPage(pPainter, pTexture, dDeltaTime);
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::drawElectricalPage(QPainter* pPainter, CTexture* pTexture, double dDeltaTime)
{
    Q_UNUSED(dDeltaTime);

    double dELEC_Gen1_Power_v = GETDATA_DOUBLE(adELEC_Gen1_Power_v);
    double dELEC_Gen1_Freq_hz = GETDATA_DOUBLE(adELEC_Gen1_Freq_hz);
    double dELEC_Gen2_Power_v = GETDATA_DOUBLE(adELEC_Gen2_Power_v);
    double dELEC_Gen2_Freq_hz = GETDATA_DOUBLE(adELEC_Gen2_Freq_hz);
    double dELEC_ACBus1_Power_v = GETDATA_DOUBLE(adELEC_ACBus1_Power_v);
    double dELEC_ACBus2_Power_v = GETDATA_DOUBLE(adELEC_ACBus2_Power_v);
    double dELEC_Tr1_Power_v = GETDATA_DOUBLE(adELEC_Tr1_Power_v);
    double dELEC_Tr2_Power_v = GETDATA_DOUBLE(adELEC_Tr2_Power_v);
    double dELEC_DCBus1_Power_v = GETDATA_DOUBLE(adELEC_DCBus1_Power_v);
    double dELEC_DCBus2_Power_v = GETDATA_DOUBLE(adELEC_DCBus2_Power_v);

    double X = 0.0 * pTexture->image().width();
    double Y = 0.0 * pTexture->image().height();
    double W = 1.0 * pTexture->image().width();
    double H = 1.0 * pTexture->image().height();
    double H20 = H / 22.0;
    double W5 = W / 5.0;

    QRectF rGen1     (W5 * 0.0, H20 * 14, W5, H20 * 4);
    QRectF rGen2     (W5 * 4.0, H20 * 14, W5, H20 * 4);
    QRectF rACBus1   (W5 * 0.0, H20 * 12, W5, H20 * 1);
    QRectF rACBus2   (W5 * 4.0, H20 * 12, W5, H20 * 1);
    QRectF rTr1      (W5 * 0.0, H20 *  8, W5, H20 * 3);
    QRectF rTr2      (W5 * 4.0, H20 *  8, W5, H20 * 3);
    QRectF rDCBus1   (W5 * 0.0, H20 *  4, W5, H20 * 1);
    QRectF rDCBus2   (W5 * 4.0, H20 *  4, W5, H20 * 1);
    QRectF rBat1     (W5 * 1.0, H20 *  1, W5, H20 * 3);
    QRectF rBat2     (W5 * 3.0, H20 *  1, W5, H20 * 3);
    QRectF rDCBatBus (W5 * 2.0, H20 *  3, W5, H20 * 1);
    QRectF rDCEssBus (W5 * 2.0, H20 *  8, W5, H20 * 1);

    // Set main font
    pPainter->setFont(m_fMainFont);

    // Generators
    drawGeneratorGauge(pPainter, pTexture, dDeltaTime, rGen1, "GEN 1", dELEC_Gen1_Power_v > 0.0, dELEC_Gen1_Power_v, dELEC_Gen1_Freq_hz);
    drawGeneratorGauge(pPainter, pTexture, dDeltaTime, rGen2, "GEN 2", dELEC_Gen2_Power_v > 0.0, dELEC_Gen2_Power_v, dELEC_Gen2_Freq_hz);

    // AC Bus
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rACBus1, "AC 1", dELEC_ACBus1_Power_v > 0.0);
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rACBus2, "AC 2", dELEC_ACBus2_Power_v > 0.0);

    // Transformers
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rTr1, "TR 1", dELEC_Tr1_Power_v > 0.0);
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rTr2, "TR 2", dELEC_Tr2_Power_v > 0.0);

    // DC Bus
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rDCBus1, "DC 1", dELEC_DCBus1_Power_v > 0.0);
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rDCBus2, "DC 2", dELEC_DCBus2_Power_v > 0.0);

    // Batteries
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rBat1, "BAT 1", true);
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rBat2, "BAT 2", true);

    // DC Bat Bus
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rDCBatBus, "DC BAT", true);

    // DC Ess Bus
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rDCEssBus, "DC ESS", true);
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::drawSimpleElecGauge(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, const QRectF& rRect, const QString& sName, bool bActive)
{
    Q_UNUSED(pTexture);
    Q_UNUSED(dDeltaTime);

    if (bActive)
        pPainter->setPen(A320_Color_Green);
    else
        pPainter->setPen(A320_Color_Amber);

    pPainter->drawRect(rRect);
    pPainter->drawText(rRect, Qt::AlignCenter, sName);
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::drawGeneratorGauge(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, const QRectF& rRect, const QString& sName, bool bActive, double dPower_v, double dFreq_hz)
{
    Q_UNUSED(pTexture);
    Q_UNUSED(dDeltaTime);

    double H4 = rRect.height() / 4.0;

    QRectF r1(rRect.x(), rRect.y() + H4 * 0.0, rRect.width(), H4);
    QRectF r2(rRect.x(), rRect.y() + H4 * 1.0, rRect.width(), H4);
    QRectF r3(rRect.x(), rRect.y() + H4 * 2.0, rRect.width(), H4);
    QRectF r4(rRect.x(), rRect.y() + H4 * 3.0, rRect.width(), H4);

    if (bActive)
        pPainter->setPen(A320_Color_Green);
    else
        pPainter->setPen(A320_Color_Amber);

    pPainter->drawRect(rRect);
    pPainter->drawText(r1, Qt::AlignCenter, sName);

    if (bActive)
    {
        pPainter->drawText(r3, Qt::AlignCenter, QString("%1 v").arg((int) dPower_v));
        pPainter->drawText(r4, Qt::AlignCenter, QString("%1 Hz").arg((int) dFreq_hz));
    }
    else
    {
        pPainter->drawText(r3, Qt::AlignCenter, "OFF");
    }
}
