
#pragma once

// qt-plus
#include "CInterpolator.h"

// Quick3D
#include "CGeoloc.h"

// Application
#include "components_a320_global.h"
#include "CAirbusFlightComputer.h"
#include "CAirbusFlightPlan.h"
#include "Constants.h"

//-------------------------------------------------------------------------------------------------
// Forward declarations

class C3DScene;

//-------------------------------------------------------------------------------------------------

enum EMCDUPage
{
    mpMenu,
    mpInit,
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
    void printAt(QPoint pWhere, const QString& sText, QColor cColor, bool bLarge = false);

    //!
    void printCenteredAt(QPoint pWhere, const QString& sText, QColor cColor, bool bLarge = false);

    //!
    void printTitle(const QString& sText);

    //!
    void printData(int iLine, bool bLeft, const QString& sText);

    //!
    void printCurrentPage();

    //!
    void printPage_Menu();

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

    EMCDUPage   m_ePage;
    MCDUChar    m_aScreen[MCDU_W][MCDU_H];
};
