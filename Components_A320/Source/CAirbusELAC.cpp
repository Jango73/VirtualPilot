
// qt-plus
#include "CLogger.h"

// Quick3D
#include "CConsoleBoard.h"
#include "C3DScene.h"
#include "CWing.h"
#include "CElevator.h"

// Application
#include "CAirbusELAC.h"

//-------------------------------------------------------------------------------------------------

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirbusELAC::instantiator(C3DScene* pScene)
{
    return new CAirbusELAC(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirbusELAC::CAirbusELAC(C3DScene* pScene)
    : CAirbusFlightComputer(pScene)
    , m_pidYaw(1.0, 0.0, 0.001)
    , m_pidPitch(1.0, 0.0, 0.001)
    , m_pidRoll(1.0, 0.0, 0.001)
    , m_dMaxRoll_deg(67.0)
{
}

//-------------------------------------------------------------------------------------------------

CAirbusELAC::~CAirbusELAC()
{
}

//-------------------------------------------------------------------------------------------------

void CAirbusELAC::loadParameters(const QString& sBaseFile, const CXMLNode& xComponent)
{
    CAirbusFlightComputer::loadParameters(sBaseFile, xComponent);

    CXMLNode xNode = xComponent.getNodeByTagName(ParamName_ControlSurfaces);

    m_rLeftWingTarget.setName(xNode.attributes()["LeftWingTarget"]);
    m_rRightWingTarget.setName(xNode.attributes()["RightWingTarget"]);
    m_rElevatorTarget.setName(xNode.attributes()["ElevatorTarget"]);
}

//-------------------------------------------------------------------------------------------------

void CAirbusELAC::solveLinks(C3DScene* pScene)
{
    CAirbusFlightComputer::solveLinks(pScene);

    m_rLeftWingTarget.solve(pScene, QSP<CComponent>(this));
    m_rRightWingTarget.solve(pScene, QSP<CComponent>(this));
    m_rElevatorTarget.solve(pScene, QSP<CComponent>(this));
}

//-------------------------------------------------------------------------------------------------

void CAirbusELAC::clearLinks(C3DScene* pScene)
{
    CAirbusFlightComputer::clearLinks(pScene);

    m_rLeftWingTarget.clear();
    m_rRightWingTarget.clear();
    m_rElevatorTarget.clear();
}

//-------------------------------------------------------------------------------------------------

void CAirbusELAC::update(double dDeltaTime)
{
    CAirbusFlightComputer::update(dDeltaTime);
}

//-------------------------------------------------------------------------------------------------

void CAirbusELAC::work(double dDeltaTime)
{
    CAirbusFlightComputer::work(dDeltaTime);

    if (m_iUnitIndex == 0)
    {
        QSP<CWing> pLeftWing = QSP_CAST(CWing, m_rLeftWingTarget.component());
        QSP<CWing> pRightWing = QSP_CAST(CWing, m_rRightWingTarget.component());
        QSP<CElevator> pElevator = QSP_CAST(CElevator, m_rElevatorTarget.component());

        double dInertial_Roll_deg = GETDATA_DOUBLE(adInertial_Roll_deg);
        double dInertial_Pitch_deg = GETDATA_DOUBLE(adInertial_Pitch_deg);
        double dInertial_RollVelocity_ds = GETDATA_DOUBLE(adInertial_RollVelocity_ds);
        double dInertial_PitchVelocity_ds = GETDATA_DOUBLE(adInertial_PitchVelocity_ds);
        double dFG_CommandedRollVelocity_ds = GETDATA_DOUBLE(adFG_CommandedRollVelocity_ds);
        double dFG_CommandedPitchVelocity_ds = GETDATA_DOUBLE(adFG_CommandedPitchVelocity_ds);
        bool bFCU_AutoPilot1_Engaged = GETDATA_BOOL(adFCU_AutoPilot1_Engaged_bool);
        bool bFCU_AutoPilot2_Engaged = GETDATA_BOOL(adFCU_AutoPilot2_Engaged_bool);
        m_vStick.X = GETDATA_DOUBLE(adStick_CAPT_x);
        m_vStick.Y = GETDATA_DOUBLE(adStick_CAPT_y);

        Q_UNUSED(bFCU_AutoPilot2_Engaged);

        //-----------------------------------------------------------------------------

        if (m_vStick.X == 0.0 && m_vStickPrevious.X != 0.0)
        {
            m_vCommandedAttitude.Z = dInertial_Roll_deg;
        }

        if (m_vStick.Y == 0.0 && m_vStickPrevious.Y != 0.0)
        {
            m_vCommandedAttitude.X = dInertial_Pitch_deg;
        }

        if (bFCU_AutoPilot1_Engaged == false && bFCU_AutoPilot1_Engaged == false)
        {
            if (m_vStick.X != 0.0)
            {
                dFG_CommandedRollVelocity_ds = m_vStick.X * -10.0;
            }
            else
            {
                dFG_CommandedRollVelocity_ds = (m_vCommandedAttitude.Z - dInertial_Roll_deg) * 5.0;
                dFG_CommandedRollVelocity_ds = Math::Angles::clipDouble(dFG_CommandedRollVelocity_ds, -10.0, 10.0);
            }

            if (m_vStick.Y != 0.0)
            {
                dFG_CommandedPitchVelocity_ds = m_vStick.Y * -5.0;
            }
            else
            {
                dFG_CommandedPitchVelocity_ds = (m_vCommandedAttitude.X - dInertial_Pitch_deg) * 10.0;
                dFG_CommandedPitchVelocity_ds = Math::Angles::clipDouble(dFG_CommandedPitchVelocity_ds, -5.0, 5.0);
            }
        }

        //-----------------------------------------------------------------------------
        // Flight enveloppe protection

        double dNormalizedRoll = Math::Angles::clipAngleDegreePIMinusPI(dInertial_Roll_deg);

        if (
                (dFG_CommandedRollVelocity_ds > 0.0 && dNormalizedRoll >= m_dMaxRoll_deg) ||
                (dFG_CommandedRollVelocity_ds < 0.0 && dNormalizedRoll <= -m_dMaxRoll_deg)
                )
        {
            dFG_CommandedRollVelocity_ds = 0.0;
        }

        //-----------------------------------------------------------------------------
        // Compute roll PID

        m_pidRoll.setSetPoint(dFG_CommandedRollVelocity_ds);
        m_pidRoll.update(dInertial_RollVelocity_ds, dDeltaTime * 1000.0);

        double dRollOutput = m_pidRoll.output();

        if (pLeftWing && pRightWing)
        {
            pLeftWing->setAileronAngle_norm(-dRollOutput);
            pRightWing->setAileronAngle_norm(dRollOutput);
        }

        //-----------------------------------------------------------------------------
        // Compute pitch PID

        m_pidPitch.setSetPoint(dFG_CommandedPitchVelocity_ds);
        m_pidPitch.update(dInertial_PitchVelocity_ds, dDeltaTime * 1000.0);

        double dPitchOutput = m_pidPitch.output();

        if (pElevator != nullptr)
        {
            pElevator->setAileronAngle_norm(-dPitchOutput);
        }

        LOG_VALUE(QString("%1 ROLL PID").arg(m_sName),
                  QString("%1")
                  .arg(QString::number(dRollOutput, 'f', 4))
                  );

        m_vStickPrevious = m_vStick;
    }
}
