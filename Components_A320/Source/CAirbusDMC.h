
#pragma once

// qt-plus
#include "CInterpolator.h"

// Quick3D
#include "CGeoloc.h"

// Application
#include "components_a320_global.h"
#include "Constants.h"
#include "CAirbusFlightComputer.h"
#include "CAirbusFlightPlan.h"
#include "../../Components_Generic/Source/CNavaidDatabase.h"

//-------------------------------------------------------------------------------------------------

class C3DScene;

//-------------------------------------------------------------------------------------------------

//! Data Monitoring Computer
class COMPONENTS_A320_EXPORT CAirbusDMC : public CAirbusFlightComputer
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    static CComponent* instantiator(C3DScene* pScene);

    //!
    CAirbusDMC(C3DScene* pScene);

    //!
    virtual ~CAirbusDMC();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Overridden methods
    //-------------------------------------------------------------------------------------------------

    //!
    virtual QString getClassName() const Q_DECL_OVERRIDE { return ClassName_CAirbusDMC; }

    //!
    virtual void update(double dDeltaTime) Q_DECL_OVERRIDE;

    //!
    virtual void updateTexture(CTexture* pTexture, double dDeltaTime) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Protected control methods
    //-------------------------------------------------------------------------------------------------

    //!
    void updateTexture_PFD(QPainter* pPainter, CTexture* pTexture, double dDeltaTime);

    //!
    void updateTexture_ND(QPainter* pPainter, CTexture* pTexture, double dDeltaTime);

    //!
    void updateTexture_EWD(QPainter* pPainter, CTexture* pTexture, double dDeltaTime);

    //!
    void updateTexture_SD(QPainter* pPainter, CTexture* pTexture, double dDeltaTime);

    //!
    void drawVelocityBar(QPainter* pPainter, CTexture* pTexture, double dDeltaTime);

    //!
    void drawArtificialHorizon(QPainter* pPainter, CTexture* pTexture, double dDeltaTime);

    //!
    void drawAltitudeBar(QPainter* pPainter, CTexture* pTexture, double dDeltaTime);

    //!
    void drawFMA(QPainter* pPainter, CTexture* pTexture, double dDeltaTime);

    //!
    void drawCompass(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, bool bArc);

    //!
    void drawNavaid(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, const CNavaid* pNavaid, const QRectF& rect);

    //!
    void drawWaypoint(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, const CWaypoint& wWaypoint, const QRectF& rect, bool bIsFlight);

    //!
    void drawEngineN1Gauge(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, const QRectF& rRect, double dN1);

    //!
    void drawSDTitle(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, const QString& sText);

    //!
    void drawStraightLine(QPainter* pPainter, const QPointF& p1, const QPointF& p2);

    //!
    void drawAutoPath(QPainter* pPainter, const QPointF& p1, const QPointF& p2);

    //!
    void drawElectricalPage(QPainter* pPainter, CTexture* pTexture, double dDeltaTime);

    //!
    void drawSimpleElecGauge(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, const QRectF& rRect, const QString& sName, bool bActive, bool bNoBordersWhenOff = false);

    //!
    void drawGeneratorGauge(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, const QRectF& rRect, const QString& sName, bool bActive, double dPower_v, double dFreq_hz, bool bNoBordersWhenOff = false);

    //!
    void drawBatGauge(QPainter* pPainter, CTexture* pTexture, double dDeltaTime, const QRectF& rRect, const QString& sName, bool bActive, double dPower_v, double dLoad_a);

    //!
    void drawHydraulicPage(QPainter* pPainter, CTexture* pTexture, double dDeltaTime);

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    QVector<CGeolocalized*>     m_vNavaids;
    QDateTime                   m_tNavaidsRefreshTime;

    int                         m_iLastHeight;

    QRectF                      m_rVelocityBar;
    QRectF                      m_rArtificialHorizon;
    QRectF                      m_rAltitudeBar;
    QRectF                      m_rFMA;
    CInterpolator<double>       m_iVerticalSpeedMarker;

    QRectF                      m_rCompass;

    QRectF                      m_rEWD_Engines;
    QRectF                      m_rEWD_Flaps;
    QRectF                      m_rEWD_Checklist;

    QFont                       m_fFontLarge;
    QFont                       m_fFontSmall;

    QPen                        m_pAmberThin;
    QPen                        m_pBlueThin;
    QPen                        m_pGreenThin;
    QPen                        m_pPurpleThin;
    QPen                        m_pWhiteThin;
    QPen                        m_pYellowThin;

    QPen                        m_pAmberBold;
    QPen                        m_pBlueBold;
    QPen                        m_pGreenBold;
    QPen                        m_pPurpleBold;
    QPen                        m_pWhiteBold;
    QPen                        m_pYellowBold;

    QPen                        m_pWhiteDashed;
};
