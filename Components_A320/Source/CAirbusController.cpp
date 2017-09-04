
// Quick3D
#include "CConsoleBoard.h"

// Application
#include "CAirbusController.h"

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusController::instantiator(C3DScene* pScene)
{
    return new CAirbusController(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusController::CAirbusController(C3DScene* pScene)
    : CAircraftController(pScene)
    , m_dEngine1ThrustLever_norm(0.0)
    , m_dEngine2ThrustLever_norm(0.0)
{
    initializeLists();
}

//-------------------------------------------------------------------------------------------------

CAirbusController::~CAirbusController()
{
}

//-------------------------------------------------------------------------------------------------

void CAirbusController::loadParameters(const QString& sBaseFile, CXMLNode xNode)
{
    CAircraftController::loadParameters(sBaseFile, xNode);

    m_rFCU.setName(xNode.attributes()["FCU"]);
    m_rMCDU_1.setName(xNode.attributes()["MCDU_1"]);
    m_rMCDU_2.setName(xNode.attributes()["MCDU_2"]);
}

//-------------------------------------------------------------------------------------------------

void CAirbusController::solveLinks(C3DScene* pScene)
{
    CAircraftController::solveLinks(pScene);

    m_rFCU.solve(pScene, QSP<CComponent>(this));
    m_rMCDU_1.solve(pScene, QSP<CComponent>(this));
    m_rMCDU_2.solve(pScene, QSP<CComponent>(this));
}

//-------------------------------------------------------------------------------------------------

void CAirbusController::clearLinks(C3DScene* pScene)
{
    CAircraftController::clearLinks(pScene);

    m_rFCU.clear();
    m_rMCDU_1.clear();
    m_rMCDU_2.clear();
}

//-------------------------------------------------------------------------------------------------

void CAirbusController::update(double dDeltaTime)
{
    CController::update(dDeltaTime);

    if (m_pJoystick != nullptr && m_pJoystick->connected())
    {
        LOG_VALUE(QString("JOY X / Y / Z / R"),
                  QString("%1 / %2 / %3 / %4")
                  .arg(QString::number(m_pJoystick->axisStates()[0], 'f', 2))
                .arg(QString::number(m_pJoystick->axisStates()[1], 'f', 2))
                .arg(QString::number(m_pJoystick->axisStates()[2], 'f', 2))
                .arg(QString::number(m_pJoystick->axisStates()[3], 'f', 2))
                );

        CVector2 vStick = CVector2(m_pJoystick->axisStates()[0], m_pJoystick->axisStates()[1]);
        double dThrottle = 1.0 - ((m_pJoystick->axisStates()[2] + 1.0) * 0.5);

        pushData(CAirbusData(m_sName, adStick_CAPT_x, vStick.X, false));
        pushData(CAirbusData(m_sName, adStick_CAPT_y, vStick.Y, false));
        pushData(CAirbusData(m_sName, adThrottle_1_norm, dThrottle, false));
        pushData(CAirbusData(m_sName, adThrottle_2_norm, dThrottle, false));
    }
    else
    {
        if (m_bAileronLeft)
        {
            pushData(CAirbusData(m_sName, adStick_CAPT_x, -1.0, false));
        }
        else if (m_bAileronRight)
        {
            pushData(CAirbusData(m_sName, adStick_CAPT_x, 1.0, false));
        }
        else
        {
            pushData(CAirbusData(m_sName, adStick_CAPT_x, 0.0, false));
        }

        if (m_bNoseUp)
        {
            pushData(CAirbusData(m_sName, adStick_CAPT_y, 1.0, false));
        }
        else if (m_bNoseDown)
        {
            pushData(CAirbusData(m_sName, adStick_CAPT_y, -1.0, false));
        }
        else
        {
            pushData(CAirbusData(m_sName, adStick_CAPT_y, 0.0, false));
        }

        if (m_bRudderLeft)
        {
            pushData(CAirbusData(m_sName, adRudder_CAPT, -1.0, false));
        }
        else if (m_bRudderRight)
        {
            pushData(CAirbusData(m_sName, adRudder_CAPT, 1.0, false));
        }
        else
        {
            pushData(CAirbusData(m_sName, adRudder_CAPT, 0.0, false));
        }

        if (m_bEngine1ThrustUp)
        {
            m_dEngine1ThrustLever_norm += 0.05;
        }
        else if (m_bEngine1ThrustDown)
        {
            m_dEngine1ThrustLever_norm -= 0.05;
        }

        if (m_bEngine2ThrustUp)
        {
            m_dEngine2ThrustLever_norm += 0.05;
        }
        else if (m_bEngine2ThrustDown)
        {
            m_dEngine2ThrustLever_norm -= 0.05;
        }

        pushData(CAirbusData(m_sName, adThrottle_1_norm, m_dEngine1ThrustLever_norm, false));
        pushData(CAirbusData(m_sName, adThrottle_2_norm, m_dEngine2ThrustLever_norm, false));
    }

    sendData();
}

//-------------------------------------------------------------------------------------------------

void CAirbusController::keyPressEvent(QKeyEvent* event)
{
    CAircraftController::keyPressEvent(event);

    switch (event->key())
    {
        case Qt::Key_Space:
            generateQ3DEvent(CQ3DEvent(EventName_Jump500, CQ3DEvent::Press));
            break;
        case Qt::Key_A:
            if (m_bControlPressed)
            {
                generateQ3DEvent(CQ3DEvent(EventName_FCU_AP2, CQ3DEvent::Press));
            }
            else
            {
                generateQ3DEvent(CQ3DEvent(EventName_FCU_AP1, CQ3DEvent::Press));
            }
            break;
        case Qt::Key_T:
            generateQ3DEvent(CQ3DEvent(EventName_FCU_ATHR, CQ3DEvent::Press));
            break;
        case Qt::Key_Right:
            if (event->modifiers() & Qt::ControlModifier)
            {
                generateQ3DEvent(CQ3DEvent(EventName_MCDU_CAPT_RIGHT, CQ3DEvent::Press));
            }
            else
            {
                generateQ3DEvent(CQ3DEvent(EventName_FCU_SEL_HEADING_INC, CQ3DEvent::Press));
            }
            break;
        case Qt::Key_Left:
            if (event->modifiers() & Qt::ControlModifier)
            {
                generateQ3DEvent(CQ3DEvent(EventName_MCDU_CAPT_LEFT, CQ3DEvent::Press));
            }
            else
            {
                generateQ3DEvent(CQ3DEvent(EventName_FCU_SEL_HEADING_DEC, CQ3DEvent::Press));
            }
            break;
        case Qt::Key_I:
            if (event->modifiers() & Qt::ControlModifier)
            {
                generateQ3DEvent(CQ3DEvent(EventName_MCDU_CAPT_INIT, CQ3DEvent::Press));
            }
            break;
        case Qt::Key_M:
            if (event->modifiers() & Qt::ControlModifier)
            {
                generateQ3DEvent(CQ3DEvent(EventName_MCDU_CAPT_MENU, CQ3DEvent::Press));
            }
            break;
        case Qt::Key_F:
            if (event->modifiers() & Qt::ControlModifier)
            {
                generateQ3DEvent(CQ3DEvent(EventName_MCDU_CAPT_FPLN, CQ3DEvent::Press));
            }
            break;
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusController::keyReleaseEvent(QKeyEvent *event)
{
    CAircraftController::keyReleaseEvent(event);
}

//-------------------------------------------------------------------------------------------------

void CAirbusController::wheelEvent(QWheelEvent *event)
{
    double dDelta = (double) event->delta() * -0.1;

    if (m_rLookTarget.component() && m_rLookTarget.component()->isCamera())
    {
        QSP<CCamera> pCamera = QSP_CAST(CCamera, m_rLookTarget.component());

        if (pCamera != nullptr)
        {
            double dFOV = Math::Angles::clipDouble(pCamera->verticalFOV() + dDelta, 5.0, 90.0);

            pCamera->setVerticalFOV(dFOV);
        }
    }
}

//-------------------------------------------------------------------------------------------------

void CAirbusController::q3dEvent(CQ3DEvent* event)
{
    CAircraftController::q3dEvent(event);

    QSP<CAirbusFCU> pFCU = QSP_CAST(CAirbusFCU, m_rFCU.component());
    QSP<CAirbusMCDU> pMCDU_1 = QSP_CAST(CAirbusMCDU, m_rMCDU_1.component());
    QSP<CAirbusMCDU> pMCDU_2 = QSP_CAST(CAirbusMCDU, m_rMCDU_2.component());

    if (event->getName() == EventName_Jump500)
    {
        QSP<CComponent> pRoot = root();

        if (pRoot != nullptr)
        {
            QSP<CPhysicalComponent> pPhysicalRoot = QSP_CAST(CPhysicalComponent, pRoot);

            if (pPhysicalRoot != nullptr)
            {
                CGeoloc gGeoloc = pPhysicalRoot->geoloc();
                gGeoloc.Altitude += 500.0;
                pPhysicalRoot->setGeoloc(gGeoloc);
            }
        }
        return;
    }

    if (event->getName() == EventName_FCU_AP1)
    {
        if (event->getAction() == CQ3DEvent::Press)
        {
            if (pFCU != nullptr)
            {
                pFCU->toggle_AutoPilot1_Engaged();
            }
        }
        return;
    }

    if (event->getName() == EventName_FCU_AP2)
    {
        if (event->getAction() == CQ3DEvent::Press)
        {
            if (pFCU != nullptr)
            {
                pFCU->toggle_AutoPilot2_Engaged();
            }
        }
        return;
    }

    if (event->getName() == EventName_FCU_ATHR)
    {
        if (event->getAction() == CQ3DEvent::Press)
        {
            if (pFCU != nullptr)
            {
                pFCU->toggle_AutoThrust_Engaged();
            }
        }
        return;
    }

    if (event->getName() == EventName_FCU_SEL_HEADING_INC)
    {
        if (event->getAction() == CQ3DEvent::Press)
        {
            if (pFCU != nullptr)
            {
                pFCU->increment_SelectedHeading(false);
            }
        }
        return;
    }

    if (event->getName() == EventName_FCU_SEL_HEADING_DEC)
    {
        if (event->getAction() == CQ3DEvent::Press)
        {
            if (pFCU != nullptr)
            {
                pFCU->decrement_SelectedHeading(false);
            }
        }
        return;
    }

    if (m_lEVENTS_MCDU_1.contains(event->getName()) && pMCDU_1 != nullptr)
    {
        pMCDU_1->handleEvent(event);
        return;
    }

    if (m_lEVENTS_MCDU_2.contains(event->getName()) && pMCDU_2 != nullptr)
    {
        pMCDU_2->handleEvent(event);
        return;
    }
}

void CAirbusController::initializeLists()
{
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_1L;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_2L;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_3L;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_4L;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_5L;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_6L;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_1R;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_2R;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_3R;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_4R;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_5R;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_6R;

    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_INIT;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_FPLN;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_MENU;

    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_UP;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_DOWN;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_LEFT;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_RIGHT;

    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_0;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_1;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_2;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_3;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_4;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_5;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_6;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_7;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_8;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_9;

    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_A;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_B;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_C;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_D;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_E;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_F;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_G;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_H;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_I;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_J;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_K;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_L;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_M;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_N;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_O;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_P;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_Q;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_R;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_S;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_T;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_U;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_V;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_W;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_X;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_Y;
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_Z;

    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_1L;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_2L;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_3L;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_4L;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_5L;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_6L;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_1R;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_2R;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_3R;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_4R;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_5R;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_6R;

    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_INIT;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_FPLN;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_MENU;

    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_UP;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_DOWN;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_LEFT;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_RIGHT;

    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_0;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_1;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_2;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_3;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_4;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_5;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_6;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_7;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_8;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_9;

    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_A;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_B;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_C;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_D;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_E;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_F;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_G;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_H;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_I;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_J;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_K;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_L;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_M;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_N;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_O;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_P;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_Q;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_R;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_S;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_T;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_U;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_V;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_W;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_X;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_Y;
    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_Z;
}
