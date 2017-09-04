
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
    ESDPage eSD_Page_idx = (ESDPage) GETDATA_INT(adSD_Page_idx);

    pPainter->resetTransform();

    pPainter->fillRect(0, 0, pTexture->image().width(), pTexture->image().height(), QColor(0, 0, 0));

    switch (eSD_Page_idx)
    {
        case sdpElectrical:
            drawElectricalPage(pPainter, pTexture, dDeltaTime);
            break;

        case sdpHydraulic:
            drawHydraulicPage(pPainter, pTexture, dDeltaTime);
            break;
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::drawSDTitle(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, const QString& sText)
{
    Q_UNUSED(dDeltaTime);

    double W = pTexture->image().width();
    double H = pTexture->image().height();
    double H22 = H / 22.0;

    QRectF rect(0.0, 0.0, W, H22);

    pPainter->setFont(m_fMainFont);
    pPainter->setPen(A320_Color_White);
    pPainter->drawText(rect, Qt::AlignLeft, sText);
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::drawStraightLine(QPainter* pPainter, const QPointF& p1, const QPointF& p2)
{
    pPainter->drawLine(p1, p2);
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::drawAutoPath(QPainter* pPainter, const QPointF& p1, const QPointF& p2)
{
    double dMidY = (p1.y() + p2.y()) * 0.5;
    pPainter->drawLine(QPointF(p1.x(), p1.y()), QPointF(p1.x(), dMidY));
    pPainter->drawLine(QPointF(p1.x(), dMidY), QPointF(p2.x(), dMidY));
    pPainter->drawLine(QPointF(p2.x(), dMidY), QPointF(p2.x(), p2.y()));
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::drawElectricalPage(QPainter* pPainter, CTexture* pTexture, double dDeltaTime)
{
    drawSDTitle(pPainter, pTexture, dDeltaTime, "ELEC");

    double dELEC_Gen1_Power_v = GETDATA_DOUBLE(adELEC_Gen1_Power_v);
    double dELEC_Gen1_Freq_hz = GETDATA_DOUBLE(adELEC_Gen1_Freq_hz);
    double dELEC_Gen2_Power_v = GETDATA_DOUBLE(adELEC_Gen2_Power_v);
    double dELEC_Gen2_Freq_hz = GETDATA_DOUBLE(adELEC_Gen2_Freq_hz);
    double dELEC_GenAPU_Power_v = GETDATA_DOUBLE(adELEC_GenAPU_Power_v);
    double dELEC_GenAPU_Freq_hz = GETDATA_DOUBLE(adELEC_GenAPU_Freq_hz);
    double dELEC_ACBus1_Power_v = GETDATA_DOUBLE(adELEC_ACBus1_Power_v);
    double dELEC_ACBus2_Power_v = GETDATA_DOUBLE(adELEC_ACBus2_Power_v);
    double dELEC_Tr1_Power_v = GETDATA_DOUBLE(adELEC_Tr1_Power_v);
    double dELEC_Tr1_Load_a = GETDATA_DOUBLE(adELEC_Tr1_Load_a);
    double dELEC_Tr2_Power_v = GETDATA_DOUBLE(adELEC_Tr2_Power_v);
    double dELEC_Tr2_Load_a = GETDATA_DOUBLE(adELEC_Tr2_Load_a);
    double dELEC_DCBus1_Power_v = GETDATA_DOUBLE(adELEC_DCBus1_Power_v);
    double dELEC_DCBus2_Power_v = GETDATA_DOUBLE(adELEC_DCBus2_Power_v);
    double dELEC_DCBatBus_Power_v = GETDATA_DOUBLE(adELEC_DCBatBus_Power_v);
    double dELEC_DCEssBus_Power_v = GETDATA_DOUBLE(adELEC_DCEssBus_Power_v);
    double dELEC_ACEssBus_Power_v = GETDATA_DOUBLE(adELEC_ACEssBus_Power_v);

    bool bELEC_Cont_Gen1_bool = GETDATA_BOOL(adELEC_Cont_Gen1_bool);
    bool bELEC_Cont_Gen2_bool = GETDATA_BOOL(adELEC_Cont_Gen2_bool);
    bool bELEC_Cont_GenAPU_1_bool = GETDATA_BOOL(adELEC_Cont_GenAPU_1_bool);
    bool bELEC_Cont_GenAPU_2_bool = GETDATA_BOOL(adELEC_Cont_GenAPU_2_bool);
    bool bELEC_Cont_Tr1_bool = GETDATA_BOOL(adELEC_Cont_Tr1_bool);
    bool bELEC_Cont_Tr2_bool = GETDATA_BOOL(adELEC_Cont_Tr2_bool);
    bool bELEC_Cont_ACEssFeed_1_bool = GETDATA_BOOL(adELEC_Cont_ACEssFeed_1_bool);
    bool bELEC_Cont_ACEssFeed_2_bool = GETDATA_BOOL(adELEC_Cont_ACEssFeed_2_bool);

    double W = pTexture->image().width();
    double H = pTexture->image().height();
    double H22 = H / 22.0;
    double W5 = W / 5.0;
    double W50 = W / 50.0;

    QRectF rGen1     (W5 * 0.0, H22 * 13, W5, H22 * 4);
    QRectF rGen2     (W5 * 4.0, H22 * 13, W5, H22 * 4);
    QRectF rAPUGen   (W5 * 2.0, H22 * 13, W5, H22 * 4);
    QRectF rACBus1   (W5 * 0.0, H22 * 11, W5, H22 * 1);
    QRectF rACBus2   (W5 * 4.0, H22 * 11, W5, H22 * 1);
    QRectF rTr1      (W5 * 0.0, H22 *  7, W5, H22 * 3);
    QRectF rTr2      (W5 * 4.0, H22 *  7, W5, H22 * 3);
    QRectF rDCBus1   (W5 * 0.0, H22 *  4, W5, H22 * 1);
    QRectF rDCBus2   (W5 * 4.0, H22 *  4, W5, H22 * 1);
    QRectF rBat1     (W5 * 1.0, H22 *  1, W5, H22 * 3);
    QRectF rBat2     (W5 * 3.0, H22 *  1, W5, H22 * 3);
    QRectF rDCBatBus (W5 * 2.0, H22 *  3, W5, H22 * 1);
    QRectF rDCEssBus (W5 * 2.0, H22 *  6, W5, H22 * 1);
    QRectF rACEssBus (W5 * 2.0, H22 * 12, W5, H22 * 1);

    rGen1.adjust     (W50, 0.0, -W50, 0.0);
    rGen2.adjust     (W50, 0.0, -W50, 0.0);
    rACBus1.adjust   (W50, 0.0, -W50, 0.0);
    rACBus2.adjust   (W50, 0.0, -W50, 0.0);
    rTr1.adjust      (W50, 0.0, -W50, 0.0);
    rTr2.adjust      (W50, 0.0, -W50, 0.0);
    rDCBus1.adjust   (W50, 0.0, -W50, 0.0);
    rDCBus2.adjust   (W50, 0.0, -W50, 0.0);
    rBat1.adjust     (W50, 0.0, -W50, 0.0);
    rBat2.adjust     (W50, 0.0, -W50, 0.0);
    rDCBatBus.adjust (W50, 0.0, -W50, 0.0);
    rDCEssBus.adjust (W50, 0.0, -W50, 0.0);
    rACEssBus.adjust (W50, 0.0, -W50, 0.0);

    // Set main font
    pPainter->setFont(m_fMainFont);

    // Generators
    drawGeneratorGauge(pPainter, pTexture, dDeltaTime, rGen1, "GEN 1", dELEC_Gen1_Power_v > 0.0, dELEC_Gen1_Power_v, dELEC_Gen1_Freq_hz);
    drawGeneratorGauge(pPainter, pTexture, dDeltaTime, rGen2, "GEN 2", dELEC_Gen2_Power_v > 0.0, dELEC_Gen2_Power_v, dELEC_Gen2_Freq_hz);
    drawGeneratorGauge(pPainter, pTexture, dDeltaTime, rAPUGen, "APU GEN", dELEC_GenAPU_Power_v > 0.0, dELEC_GenAPU_Power_v, dELEC_GenAPU_Freq_hz);

    // AC Bus
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rACBus1, "AC 1", dELEC_ACBus1_Power_v > 0.0);
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rACBus2, "AC 2", dELEC_ACBus2_Power_v > 0.0);

    // Transformers
    drawBatGauge(pPainter, pTexture, dDeltaTime, rTr1, "TR 1", dELEC_Tr1_Power_v > 0.0, dELEC_Tr1_Power_v, dELEC_Tr1_Load_a);
    drawBatGauge(pPainter, pTexture, dDeltaTime, rTr2, "TR 2", dELEC_Tr2_Power_v > 0.0, dELEC_Tr2_Power_v, dELEC_Tr2_Load_a);

    // DC Bus
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rDCBus1, "DC 1", dELEC_DCBus1_Power_v > 0.0);
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rDCBus2, "DC 2", dELEC_DCBus2_Power_v > 0.0);

    // Batteries
    drawBatGauge(pPainter, pTexture, dDeltaTime, rBat1, "BAT 1", true, 28.0, 0.0);
    drawBatGauge(pPainter, pTexture, dDeltaTime, rBat2, "BAT 2", true, 28.0, 0.0);

    // DC Bat Bus
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rDCBatBus, "DC BAT", dELEC_DCBatBus_Power_v > 0.0);

    // DC Ess Bus
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rDCEssBus, "DC ESS", dELEC_DCEssBus_Power_v > 0.0);

    // AC Ess Bus
    drawSimpleElecGauge(pPainter, pTexture, dDeltaTime, rACEssBus, "AC ESS", dELEC_ACEssBus_Power_v > 0.0);

    QPen linePen(QBrush(A320_Color_Green), 2);
    pPainter->setPen(linePen);

    // Gen1 contactor
    if (bELEC_Cont_Gen1_bool)
    {
        drawStraightLine(pPainter, QPointF(rGen1.center().x(), rGen1.top()), QPointF(rGen1.center().x(), rACBus1.bottom()));
    }
    else if (bELEC_Cont_GenAPU_1_bool)
    {
        drawAutoPath(pPainter, QPointF(rAPUGen.center().x(), rAPUGen.top()), QPointF(rACBus1.center().x(), rACBus1.bottom()));
    }

    // Gen2 contactor
    if (bELEC_Cont_Gen2_bool)
    {
        drawStraightLine(pPainter, QPointF(rGen2.center().x(), rGen2.top()), QPointF(rACBus2.center().x(), rACBus2.bottom()));
    }
    else if (bELEC_Cont_GenAPU_2_bool)
    {
        drawAutoPath(pPainter, QPointF(rAPUGen.center().x(), rAPUGen.top()), QPointF(rACBus2.center().x(), rACBus2.bottom()));
    }

    // AC Ess Feed 1 contactor
    if (bELEC_Cont_ACEssFeed_1_bool)
    {
        drawStraightLine(pPainter, QPointF(rACBus1.right(), rACBus1.center().y()), QPointF(rACEssBus.left(), rACEssBus.center().y()));
    }

    // AC Ess Feed 2 contactor
    if (bELEC_Cont_ACEssFeed_2_bool)
    {
        drawStraightLine(pPainter, QPointF(rACEssBus.right(), rACEssBus.center().y()), QPointF(rACBus2.left(), rACBus2.center().y()));
    }

    // Tr1 contactor
    if (bELEC_Cont_Tr1_bool)
    {
        drawStraightLine(pPainter, QPointF(rACBus1.center().x(), rACBus1.top()), QPointF(rTr1.center().x(), rTr1.bottom()));
    }

    // Tr2 contactor
    if (bELEC_Cont_Tr2_bool)
    {
        drawStraightLine(pPainter, QPointF(rACBus2.center().x(), rACBus2.top()), QPointF(rTr2.center().x(), rTr2.bottom()));
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::drawSimpleElecGauge(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, const QRectF& rRect, const QString& sName, bool bActive)
{
    Q_UNUSED(pTexture);
    Q_UNUSED(dDeltaTime);

    pPainter->fillRect(rRect, A320_Color_Gray);

    if (bActive)
        pPainter->setPen(A320_Color_Green);
    else
        pPainter->setPen(A320_Color_Amber);

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

    pPainter->setPen(A320_Color_White);
    pPainter->drawRect(rRect);
    pPainter->drawText(r1, Qt::AlignCenter, sName);

    if (bActive)
        pPainter->setPen(A320_Color_Green);
    else
        pPainter->setPen(A320_Color_Amber);

    if (bActive)
    {
        pPainter->drawText(r2, Qt::AlignCenter, QString("%1%").arg((int) 25));
        pPainter->drawText(r3, Qt::AlignCenter, QString("%1 V").arg((int) dPower_v));
        pPainter->drawText(r4, Qt::AlignCenter, QString("%1 Hz").arg((int) dFreq_hz));
    }
    else
    {
        pPainter->drawText(r3, Qt::AlignCenter, "OFF");
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::drawBatGauge(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, const QRectF& rRect, const QString& sName, bool bActive, double dPower_v, double dLoad_a)
{
    Q_UNUSED(pTexture);
    Q_UNUSED(dDeltaTime);

    double H3 = rRect.height() / 3.0;

    QRectF r1(rRect.x(), rRect.y() + H3 * 0.0, rRect.width(), H3);
    QRectF r2(rRect.x(), rRect.y() + H3 * 1.0, rRect.width(), H3);
    QRectF r3(rRect.x(), rRect.y() + H3 * 2.0, rRect.width(), H3);

    pPainter->setPen(A320_Color_White);
    pPainter->drawRect(rRect);
    pPainter->drawText(r1, Qt::AlignCenter, sName);

    if (bActive)
        pPainter->setPen(A320_Color_Green);
    else
        pPainter->setPen(A320_Color_Amber);

    if (bActive)
    {
        pPainter->drawText(r2, Qt::AlignCenter, QString("%1 V").arg((int) dPower_v));
        pPainter->drawText(r3, Qt::AlignCenter, QString("%1 A").arg((int) dLoad_a));
    }
    else
    {
        pPainter->drawText(r3, Qt::AlignCenter, "OFF");
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::drawHydraulicPage(QPainter* pPainter, CTexture* pTexture, double dDeltaTime)
{
    drawSDTitle(pPainter, pTexture, dDeltaTime, "HYD");
}
