
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

void CAirbusDMC::updateTexture_ND(QPainter* pPainter, CTexture* pTexture, double dDeltaTime)
{
    drawCompass(pPainter, pTexture, dDeltaTime, true);
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::drawCompass(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, bool bArc)
{
    // Get flight data
    CAirbusFlightPlan* pFG_FlightPlan_ptr = GETDATA_POINTER(adFG_FlightPlan_ptr, CAirbusFlightPlan);
    double dGeoLoc_Latitude_deg = GETDATA_DOUBLE(adGeoLoc_Latitude_deg);
    double dGeoLoc_Longitude_deg = GETDATA_DOUBLE(adGeoLoc_Longitude_deg);
    double dGeoLoc_TrueHeading_deg = GETDATA_DOUBLE(adGeoLoc_TrueHeading_deg);
    double dGeoLoc_TrueTrack_deg = GETDATA_DOUBLE(adGeoLoc_TrueTrack_deg);
    double dFCU_Heading_deg = GETDATA_DOUBLE(adFCU_Heading_deg);

    //-----------------------------------------------------------------------------

    double dRange_m = 40 * FAC_NM_TO_M;

    // Compute coordinates
    double X = m_rCompass.left() * pTexture->image().width();
    double Y = m_rCompass.top() * pTexture->image().height();
    double W = m_rCompass.width() * pTexture->image().width();
    double H = m_rCompass.height() * pTexture->image().height();

    double W8 = W / 8.0;
    double W10 = W / 10.0;
    double W20 = W / 20.0;
    double W30 = W / 30.0;
    double H2 = H / 2.0;
    double H8 = H / 8.0;
    double H20 = H / 20.0;
    double H40 = H / 40.0;

    if (bArc)
    {
        X = (m_rCompass.center().x() - m_rCompass.width()) * pTexture->image().width();
        Y = m_rCompass.top() * pTexture->image().height();
        W = (m_rCompass.width() * 2.0) * pTexture->image().width();
        H = (m_rCompass.height() * 2.0) * pTexture->image().height();

        W8 = W / 16.0;
        W20 = W / 40.0;
        W30 = W / 60.0;
        H2 = H / 4.0;
        H8 = H / 16.0;
        H20 = H / 40.0;
        H40 = H / 80.0;
    }

    double dRangeFactor = (W * 0.5) / dRange_m;

    QRectF rWholePart(X, Y, W, H);

    // Set main font
    pPainter->setFont(m_fFontLarge);

    pPainter->resetTransform();

    // Main ellipses
    pPainter->setPen(m_pWhiteThin);

    pPainter->drawEllipse(rWholePart);

    pPainter->setPen(m_pWhiteDashed);

    pPainter->save();
    pPainter->translate(rWholePart.center() * 0.25);
    pPainter->scale(0.75, 0.75);
    pPainter->drawEllipse(rWholePart);
    pPainter->restore();

    pPainter->save();
    pPainter->translate(rWholePart.center() * 0.5);
    pPainter->scale(0.50, 0.50);
    pPainter->drawEllipse(rWholePart);
    pPainter->restore();

    pPainter->save();
    pPainter->translate(rWholePart.center() * 0.75);
    pPainter->scale(0.25, 0.25);
    pPainter->drawEllipse(rWholePart);
    pPainter->restore();

    pPainter->translate(rWholePart.center());

    CGeoloc gAircraftGeoloc(dGeoLoc_Latitude_deg, dGeoLoc_Longitude_deg, 0.0);
    CMatrix4 mAircraftHeading = CMatrix4::makeRotation(CVector3(0.0, Angles::toRad(-dGeoLoc_TrueHeading_deg), 0.0));

    // Navaids
    if (m_vNavaids.count() > 0)
    {
        foreach (CGeolocalized* pGeolocalized, m_vNavaids)
        {
            CNavaid* pNavaid = dynamic_cast<CNavaid*>(pGeolocalized);

            if (pNavaid != nullptr)
            {
                CVector3 vCurrentPosition = pNavaid->geoloc().toVector3(gAircraftGeoloc);
                vCurrentPosition = mAircraftHeading * vCurrentPosition;
                vCurrentPosition.Z *= -1.0;
                vCurrentPosition *= dRangeFactor;

                QRectF wpt(QPointF(vCurrentPosition.X - W30, vCurrentPosition.Z - W30), QSizeF(W30 * 2, W30 * 2));

                drawNavaid(pPainter, pTexture, dDeltaTime, pNavaid, wpt);
            }
        }
    }

    // Flight plan
    if (pFG_FlightPlan_ptr != nullptr)
    {
        CVector3 vPreviousPosition;

        for (int iIndex = 0; iIndex < pFG_FlightPlan_ptr->waypoints().count(); iIndex++)
        {
            CVector3 vCurrentPosition = pFG_FlightPlan_ptr->waypoints()[iIndex].geoloc().toVector3(gAircraftGeoloc);
            vCurrentPosition = mAircraftHeading * vCurrentPosition;
            vCurrentPosition.Z *= -1.0;
            vCurrentPosition *= dRangeFactor;

            QRectF wpt(QPointF(vCurrentPosition.X - W30, vCurrentPosition.Z - W30), QSizeF(W30 * 2, W30 * 2));

            if (iIndex > 0)
            {
                pPainter->setPen(m_pWhiteThin);
                pPainter->drawLine(vPreviousPosition.X, vPreviousPosition.Z, vCurrentPosition.X, vCurrentPosition.Z);
            }

            drawWaypoint(pPainter, pTexture, dDeltaTime, pFG_FlightPlan_ptr->waypoints()[iIndex], wpt, true);

            vPreviousPosition = vCurrentPosition;
        }
    }

    // Aircraft
    {
        QPointF point1(0.0, -W20);
        QPointF point2(0.0, W10);
        QPointF point3(-W20, 0.0);
        QPointF point4(W20, 0.0);

        pPainter->setPen(m_pYellowBold);
        pPainter->drawLine(point1, point2);
        pPainter->drawLine(point3, point4);
    }

    pPainter->rotate(-dGeoLoc_TrueHeading_deg);

    pPainter->setPen(m_pWhiteThin);

    // Marks
    pPainter->save();

    for (int iAngle = 0; iAngle < 360; iAngle += 10)
    {
        pPainter->drawLine(0.0, rWholePart.height() * -0.5, 0.0, rWholePart.height() * -0.5 - H20);
        pPainter->rotate(10);
    }

    pPainter->restore();

    pPainter->save();

    pPainter->rotate(5);
    for (int iAngle = 0; iAngle < 360; iAngle += 10)
    {
        pPainter->drawLine(0.0, rWholePart.height() * -0.5, 0.0, rWholePart.height() * -0.5 - H40);
        pPainter->rotate(10);
    }

    pPainter->restore();

    // Numbers

    {
        pPainter->save();

        for (int iAngle = 0; iAngle < 360; iAngle += 30)
        {
            QRectF rText(-W8, rWholePart.height() * -0.5 - H8 * 2.0, W8 * 2.0, H8 * 2.0);
            pPainter->drawText(rText, Qt::AlignCenter, QString::number(iAngle / 10));
            pPainter->rotate(30);
        }

        pPainter->restore();
    }

    // Selected heading

    {
        pPainter->save();

        pPainter->rotate(dFCU_Heading_deg);

        pPainter->setPen(m_pBlueThin);

        QPointF point1(0.0, rWholePart.height() * -0.5);
        QPointF point2(-W20, rWholePart.height() * -0.5 - W20);
        QPointF point3(W20, rWholePart.height() * -0.5 - W20);

        pPainter->drawLine(point1, point2);
        pPainter->drawLine(point2, point3);
        pPainter->drawLine(point3, point1);

        pPainter->restore();
    }

    // Track

    {
        pPainter->save();

        pPainter->rotate(dGeoLoc_TrueTrack_deg - dGeoLoc_TrueHeading_deg);

        pPainter->setPen(m_pGreenThin);

        QPointF point1(0.0, rWholePart.height() * -0.5);
        QPointF point2(-H40, rWholePart.height() * -0.5 + H40);
        QPointF point3(0.0, rWholePart.height() * -0.5 + H40 * 2.0);
        QPointF point4(H40, rWholePart.height() * -0.5 + H40);

        pPainter->drawLine(point1, point2);
        pPainter->drawLine(point2, point3);
        pPainter->drawLine(point3, point4);
        pPainter->drawLine(point4, point1);

        pPainter->restore();
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::drawNavaid(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, const CNavaid* pNavaid, const QRectF& rect)
{
    double W6 = rect.width() / 6.0;

    switch (pNavaid->type())
    {
        case ntNDB:
            pPainter->setPen(m_pWhiteThin);
            pPainter->drawLine(QPointF(rect.center().x(), rect.top()), QPointF(rect.right(), rect.bottom()));
            pPainter->drawLine(QPointF(rect.right(), rect.bottom()), QPointF(rect.left(), rect.bottom()));
            pPainter->drawLine(QPointF(rect.left(), rect.bottom()), QPointF(rect.center().x(), rect.top()));
            break;
        case ntVOR:
            pPainter->setPen(m_pWhiteThin);
            pPainter->drawLine(QPointF(rect.center().x(), rect.top()), QPointF(rect.center().x(), rect.bottom()));
            pPainter->drawLine(QPointF(rect.left(), rect.center().y()), QPointF(rect.right(), rect.center().y()));
        case ntVORDME:
        case ntVORTAC:
            pPainter->setPen(m_pWhiteThin);
            QRectF circleRect = rect.adjusted(W6, W6, -W6, -W6);
            pPainter->drawArc(circleRect, 0, 360 * 16);
            break;
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusDMC::drawWaypoint(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, const CWaypoint& wWaypoint, const QRectF& rect, bool bIsFlight)
{
    Q_UNUSED(pTexture);

    double dX1 = rect.left();
    double dY1 = rect.top();
    double dX2 = rect.right();
    double dY2 = rect.bottom();
    double dXC = rect.center().x();
    double dYC = rect.center().y();

    if (bIsFlight)
    {
        pPainter->setPen(m_pGreenThin);
        pPainter->drawLine(dXC, dY1, dX2, dYC);
        pPainter->drawLine(dX2, dYC, dXC, dY2);
        pPainter->drawLine(dXC, dY2, dX1, dYC);
        pPainter->drawLine(dX1, dYC, dXC, dY1);
    }
    else
    {
        switch (wWaypoint.type())
        {
            case wtAirport:
                pPainter->setPen(m_pPurpleThin);
                // pPainter->drawEllipse(wpt);
                pPainter->drawLine(dX1, dYC, dX2, dYC);
                pPainter->drawLine(dXC, dY1, dXC, dY2);
                pPainter->drawLine(dX1, dY1, dX2, dY2);
                pPainter->drawLine(dX1, dY2, dX2, dY1);
                break;

            default:
                break;
        }
    }

    QRectF rText(dX2, dYC, rect.width() * 4.0, rect.height());
    pPainter->drawText(rText, Qt::AlignLeft, wWaypoint.name());
}
