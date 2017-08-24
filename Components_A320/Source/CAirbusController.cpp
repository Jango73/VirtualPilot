
// Quick3D
#include "CConsoleBoard.h"

// Application
#include "CAirbusController.h"

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusController::instanciator(C3DScene* pScene)
{
    return new CAirbusController(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusController::CAirbusController(C3DScene* pScene)
    : CAircraftController(pScene)
{
    m_lEVENTS_MCDU_1 << EventName_MCDU_CAPT_MENU;
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

    m_lEVENTS_MCDU_2 << EventName_MCDU_FO_MENU;
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

        pushData(CAirbusData(m_sName, adStick_CAPT_x, vStick.X));
        pushData(CAirbusData(m_sName, adStick_CAPT_y, vStick.Y));
        pushData(CAirbusData(m_sName, adThrottle_1_norm, dThrottle));
        pushData(CAirbusData(m_sName, adThrottle_2_norm, dThrottle));
    }
    else
    {
        if (m_bAileronLeft)
        {
            pushData(CAirbusData(m_sName, adStick_CAPT_x, -1.0));
        }
        else if (m_bAileronRight)
        {
            pushData(CAirbusData(m_sName, adStick_CAPT_x, 1.0));
        }
        else
        {
            pushData(CAirbusData(m_sName, adStick_CAPT_x, 0.0));
        }

        if (m_bNoseUp)
        {
            pushData(CAirbusData(m_sName, adStick_CAPT_y, 1.0));
        }
        else if (m_bNoseDown)
        {
            pushData(CAirbusData(m_sName, adStick_CAPT_y, -1.0));
        }
        else
        {
            pushData(CAirbusData(m_sName, adStick_CAPT_y, 0.0));
        }

        if (m_bRudderLeft)
        {
            pushData(CAirbusData(m_sName, adRudder_CAPT, -1.0));
        }
        else if (m_bRudderRight)
        {
            pushData(CAirbusData(m_sName, adRudder_CAPT, 1.0));
        }
        else
        {
            pushData(CAirbusData(m_sName, adRudder_CAPT, 0.0));
        }
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
            generateQ3DEvent(CQ3DEvent(EventName_FCU_SEL_HEADING_INC, CQ3DEvent::Press));
            break;
        case Qt::Key_Left:
            generateQ3DEvent(CQ3DEvent(EventName_FCU_SEL_HEADING_DEC, CQ3DEvent::Press));
            break;
        case Qt::Key_PageUp:
            generateQ3DEvent(CQ3DEvent(EventName_THR_THROTTLE_INC, CQ3DEvent::Press));
            break;
        case Qt::Key_PageDown:
            generateQ3DEvent(CQ3DEvent(EventName_THR_THROTTLE_DEC, CQ3DEvent::Press));
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
            double dFOV = Math::Angles::clipDouble(pCamera->getFOV() + dDelta, 5.0, 120.0);

            pCamera->setFOV(dFOV);
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

    if (event->getName() == EventName_THR_THROTTLE_INC)
    {
        if (event->getAction() == CQ3DEvent::Press)
        {
            CAirbusData* pThrottle_1_norm = getData(adThrottle_1_norm);
            CAirbusData* pThrottle_2_norm = getData(adThrottle_2_norm);

            double dThrottle_1_norm = 0.0;
            double dThrottle_2_norm = 0.0;

            if (pThrottle_1_norm != nullptr)
            {
                dThrottle_1_norm = pThrottle_1_norm->getData().toDouble();
            }

            if (pThrottle_2_norm != nullptr)
            {
                dThrottle_2_norm = pThrottle_2_norm->getData().toDouble();
            }

            dThrottle_1_norm = Math::Angles::clipDouble(dThrottle_1_norm + 0.1, 0.0, 1.0);
            dThrottle_2_norm = Math::Angles::clipDouble(dThrottle_2_norm + 0.1, 0.0, 1.0);

            pushData(CAirbusData(m_sName, adThrottle_1_norm, dThrottle_1_norm));
            pushData(CAirbusData(m_sName, adThrottle_2_norm, dThrottle_2_norm));
        }
        return;
    }

    if (event->getName() == EventName_THR_THROTTLE_DEC)
    {
        if (event->getAction() == CQ3DEvent::Press)
        {
            CAirbusData* pThrottle_1_norm = getData(adThrottle_1_norm);
            CAirbusData* pThrottle_2_norm = getData(adThrottle_2_norm);

            double dThrottle_1_norm = 0.0;
            double dThrottle_2_norm = 0.0;

            if (pThrottle_1_norm != nullptr)
            {
                dThrottle_1_norm = pThrottle_1_norm->getData().toDouble();
            }

            if (pThrottle_2_norm != nullptr)
            {
                dThrottle_2_norm = pThrottle_2_norm->getData().toDouble();
            }

            dThrottle_1_norm = Math::Angles::clipDouble(dThrottle_1_norm - 0.1, 0.0, 1.0);
            dThrottle_2_norm = Math::Angles::clipDouble(dThrottle_2_norm - 0.1, 0.0, 1.0);

            pushData(CAirbusData(m_sName, adThrottle_1_norm, dThrottle_1_norm));
            pushData(CAirbusData(m_sName, adThrottle_2_norm, dThrottle_2_norm));
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
