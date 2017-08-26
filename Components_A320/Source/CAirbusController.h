
#pragma once

// Qt
#include <QKeyEvent>
#include <QMouseEvent>

// Quick3D
#include "CAircraftController.h"
#include "CComponentReference.h"

// Application
#include "components_a320_global.h"
#include "Constants.h"
#include "CAirbusDataSupplier.h"
#include "CAirbusFCU.h"
#include "CAirbusMCDU.h"

//-------------------------------------------------------------------------------------------------

class C3DScene;

//-------------------------------------------------------------------------------------------------

class COMPONENTS_A320_EXPORT CAirbusController : public CAircraftController, public CAirbusDataSupplier
{

public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    static CComponent* instanciator(C3DScene* pScene);

    //!
    CAirbusController(C3DScene* pScene);

    //!
    virtual ~CAirbusController();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //!
    void initializeLists();

    //-------------------------------------------------------------------------------------------------
    // Inherited methods
    //-------------------------------------------------------------------------------------------------

    //! Returns this object's class name
    virtual QString getClassName() const { return ClassName_CAirbusController; }

    //! Loads this object's parameters
    virtual void loadParameters(const QString& sBaseFile, CXMLNode xComponent) Q_DECL_OVERRIDE;

    //! Solves the links of this object
    virtual void solveLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //! Deletes this object's links
    virtual void clearLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //!
    virtual void update(double dDeltaTime) Q_DECL_OVERRIDE;

    //!
    virtual void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;

    //!
    virtual void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

    //!
    virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

    //!
    virtual void q3dEvent(CQ3DEvent* event) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    CComponentReference<CAirbusFCU>     m_rFCU;
    CComponentReference<CAirbusMCDU>    m_rMCDU_1;
    CComponentReference<CAirbusMCDU>    m_rMCDU_2;

    QStringList                         m_lEVENTS_MCDU_1;
    QStringList                         m_lEVENTS_MCDU_2;

    double                              m_dEngine1ThrustLever_norm;
    double                              m_dEngine2ThrustLever_norm;
};
