
#pragma once

// qt-plus
#include "CInterpolator.h"

// Quick3D
#include "CGeoloc.h"
#include "CController.h"

// Application
#include "components_a320_global.h"
#include "CAirbusFlightComputer.h"
#include "CAirbusFlightPlan.h"
#include "Constants.h"

//-------------------------------------------------------------------------------------------------
// Forward declarations

class C3DScene;

//-------------------------------------------------------------------------------------------------
// Enumerations

enum EMCDUPage
{
    mpMenu,
    mpInitA,
    mpInitB,
    mpRouteSelection,
    mpClimbWind,
    mpHistoryWind,
    mpCruiseWind,
    mpDescentWind,
    mpFuelPred,
    mpFlightPlanA,
    mpFlightPlanB,
    mpLateralRevision,
    mpDeparture
};

enum EMCDUKey
{
    mkSpace = 20, mkNot, mkQuote, mkHash, mkDollar, mkPercent, mkAnd,
    mkSingleQuote, mkOpenParent, mkCloseParen, mkStar, mkPlus, mkComma,
    mkMinus, mkDot, mkSlash,
    mk0 = 48, mk1, mk2, mk3, mk4, mk5, mk6, mk7, mk8, mk9,
    mkA = 65, mkB, mkC, mkD, mkE, mkF, mkG, mkH, mkI, mkJ, mkK, mkL, mkM,
    mkN, mkO, mkP, mkQ, mkR, mkS, mkT, mkU, mkV, mkW, mkX, mkY, mkZ,
    mk1L = 300, mk2L, mk3L, mk4L, mk5L, mk6L,
    mk1R, mk2R, mk3R, mk4R, mk5R, mk6R,
    mkUp, mkDown, mkLeft, mkRight,
    mkDep, mkProg, mkPerf, mkInit, mkData,
    mkFPln, mkRadNav, mkFuelPred, mkSecFPln, mkATCCOM, mkMenu,
    mkAirport,
    mkOverFly, mkClear
};

//-------------------------------------------------------------------------------------------------

#define CHAR_PH '\219'

#define MCDU_W  24
#define MCDU_H  14

//! Multipurpose Control and Display Unit
//! HMI for FMGC
class COMPONENTS_A320_EXPORT CAirbusMCDU : public CAirbusFlightComputer
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    static CComponent* instanciator(C3DScene* pScene);

    //!
    CAirbusMCDU(C3DScene* pScene);

    //!
    virtual ~CAirbusMCDU();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Inherited methods
    //-------------------------------------------------------------------------------------------------

    //!
    virtual QString getClassName() const { return ClassName_CAirbusMCDU; }

    //!
    virtual void update(double dDeltaTime) Q_DECL_OVERRIDE;

    //!
    virtual void updateTexture(CTexture* pTexture, double dDeltaTime);

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //!
    void handleEvent(CQ3DEvent* event);

    //!
    void handleKey(EMCDUKey eKey);

    //!
    void printAt(QPoint pWhere, const QString& sText, QColor cColor, bool bLarge = false);

    //!
    void printCenteredAt(QPoint pWhere, const QString& sText, QColor cColor, bool bLarge = false);

    //!
    void printTitle(const QString& sText);

    //!
    void printLabel(int iLine, bool bLeft, const QString& sText);

    //!
    void printData(int iLine, bool bLeft, const QString& sText);

    //!
    void printCurrentPage();

    //!
    void printScratchPad();

    //!
    void printPage_Menu();
    void handleKey_Menu(EMCDUKey eKey);

    void printPage_InitA();
    void handleKey_InitA(EMCDUKey eKey);

    void printPage_InitB();
    void handleKey_InitB(EMCDUKey eKey);

    void printPage_RouteSelection();
    void handleKey_RouteSelection(EMCDUKey eKey);

    //!
    void sendData(EMCDUDataSet eDataName, QVariant vValue);

    //-------------------------------------------------------------------------------------------------
    // Inner classes
    //-------------------------------------------------------------------------------------------------

    class MCDUChar
    {
    public:

        MCDUChar()
            : m_cChar(' ')
            , m_cColor(A320_Color_Black)
            , m_bLarge(false)
        {
        }

        QChar   m_cChar;
        QColor  m_cColor;
        bool    m_bLarge;
    };

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    EMCDUPage                   m_ePage;
    MCDUChar                    m_aScreen[MCDU_W][MCDU_H];
    QString                     m_sScratchPad;
    QMap<QString, EMCDUKey>     m_mEventToKey;
    bool                        m_bNeedScreenRefresh;
};
