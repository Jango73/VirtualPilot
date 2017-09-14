
#pragma once

// qt-plus
#include "CInterpolator.h"

// Quick3D
#include "CGeoloc.h"
#include "CComponentReference.h"
#include "CEngineGenerator.h"
#include "CElectricalBus.h"
#include "CElectricalContactor.h"

// Application
#include "components_a320_global.h"
#include "CAirbusFlightComputer.h"
#include "Constants.h"

//-------------------------------------------------------------------------------------------------

class C3DScene;

//-------------------------------------------------------------------------------------------------

//! Data Monitoring Computer
class COMPONENTS_A320_EXPORT CAirbusCFDIU : public CAirbusFlightComputer
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    static CComponent* instantiator(C3DScene* pScene);

    //!
    CAirbusCFDIU(C3DScene* pScene);

    //!
    virtual ~CAirbusCFDIU();

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
    virtual QString getClassName() const Q_DECL_OVERRIDE { return ClassName_CAirbusCFDIU; }

    //! Loads this object's parameters
    virtual void loadParameters(const QString& sBaseFile, CXMLNode xComponent) Q_DECL_OVERRIDE;

    //! Solves the links of this object
    virtual void solveLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //! Deletes this object's links
    virtual void clearLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //!
    virtual void update(double dDeltaTime) Q_DECL_OVERRIDE;

    //!
    virtual void work(double dDeltaTime) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    CComponentReference<CEngineGenerator>       m_rGenerator1;
    CComponentReference<CEngineGenerator>       m_rGenerator2;
    CComponentReference<CElectricalBus>         m_rACBus1;
    CComponentReference<CElectricalBus>         m_rACBus2;
    CComponentReference<CElectricalBus>         m_rTr1;
    CComponentReference<CElectricalBus>         m_rTr2;
    CComponentReference<CElectricalBus>         m_rEssTr;
    CComponentReference<CElectricalBus>         m_rDCBus1;
    CComponentReference<CElectricalBus>         m_rDCBus2;
    CComponentReference<CElectricalBus>         m_rDCBatBus;
    CComponentReference<CElectricalBus>         m_rDCEssBus;
    CComponentReference<CElectricalBus>         m_rACEssBus;

    CComponentReference<CElectricalContactor>   m_rContGen1;
    CComponentReference<CElectricalContactor>   m_rContGen2;
    CComponentReference<CElectricalContactor>   m_rContGenAPU;
    CComponentReference<CElectricalContactor>   m_rContACTie1;
    CComponentReference<CElectricalContactor>   m_rContACTie2;
    CComponentReference<CElectricalContactor>   m_rContTr1;
    CComponentReference<CElectricalContactor>   m_rContTr2;
    CComponentReference<CElectricalContactor>   m_rContDCTie1;
    CComponentReference<CElectricalContactor>   m_rContDCTie2;
    CComponentReference<CElectricalContactor>   m_rContEssTr;
    CComponentReference<CElectricalContactor>   m_rContACEssFeed1;
    CComponentReference<CElectricalContactor>   m_rContACEssFeed2;
};
