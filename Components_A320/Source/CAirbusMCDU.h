
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
    mkDelete = 127,
    mk1L = 300, mk2L, mk3L, mk4L, mk5L, mk6L,
    mk1R, mk2R, mk3R, mk4R, mk5R, mk6R,
    mkUp, mkDown, mkLeft, mkRight,
    mkDir, mkProg, mkPerf, mkInit, mkData,
    mkFPln, mkRadNav, mkFuelPred, mkSecFPln, mkATCCOM, mkMenu,
    mkAirport,
    mkOverFly, mkClear
};

//-------------------------------------------------------------------------------------------------

#define CHAR_PH                         '\219'

#define MCDU_SCREEN_WIDTH               24
#define MCDU_SCREEN_HEIGHT              14
#define MCDU_FPLN_WAYP_PER_PAGE         5

#define MCDU_FORMAT_COMPANY_ROUTE       "__________"
#define MCDU_FORMAT_ICAO_FROM_TO        "____/____"

#define MCDU_TEXT_FPLN_DISCONTINUITY    " F-PLN DISCONTINUITY"
#define MCDU_TEXT_FPLN_HEADER           "          UTC  SPD/ALT  "
#define MCDU_TEXT_FPLN_FOOTER           " DEST     UTC  DIST EFOB"

#define MCDU_ERROR_BAD_FORMAT           "BAD FORMAT"

//-------------------------------------------------------------------------------------------------

//! Multipurpose Control and Display Unit
//! HMI for FMGC
class COMPONENTS_A320_EXPORT CAirbusMCDU : public CAirbusFlightComputer
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    static CComponent* instantiator(C3DScene* pScene);

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
    // Overridden methods
    //-------------------------------------------------------------------------------------------------

    //!
    virtual QString getClassName() const Q_DECL_OVERRIDE { return ClassName_CAirbusMCDU; }

    //!
    virtual void update(double dDeltaTime) Q_DECL_OVERRIDE;

    //!
    virtual void updateTexture(CTexture* pTexture, double dDeltaTime) Q_DECL_OVERRIDE;

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
    void printLeftTitle(const QString& sText);

    //!
    void printLabel(int iLine, bool bLeft, const QString& sText);

    //!
    void printData(int iLine, bool bLeft, const QString& sText, QColor cColor = A320_Color_White);

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

    void printPage_FlightPlanA();
    void handleKey_FlightPlanA(EMCDUKey eKey);

    //!
    QString printableAltitude(double dAltitude_m);

    //!
    QString printableSpeed(double dSpeed_ms);

    //!
    bool respectsFormat(const QString& sValue, const QString& sFormat);

    //!
    void sendData(EMCDUDataSet eDataName, QVariant vValue);

    //!
    void fillTables();

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
    int                         m_iSubPage;
    MCDUChar                    m_aScreen[MCDU_SCREEN_WIDTH][MCDU_SCREEN_HEIGHT];
    QString                     m_sScratchPad;
    QString                     m_sError;
    QMap<QString, EMCDUKey>     m_mEventToKey;

    int                         m_iLastHeight;
    QFont                       m_fFontLarge;
    QFont                       m_fFontSmall;
};
