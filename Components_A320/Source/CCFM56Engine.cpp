
// Quick3D
#include "CConsoleBoard.h"
#include "C3DScene.h"

// Application
#include "CCFM56Engine.h"

using namespace Math;

//-------------------------------------------------------------------------------------------------

static const double IDLE_N1_NORM = 0.25;

//-------------------------------------------------------------------------------------------------

CComponent* CCFM56Engine::instantiator(C3DScene* pScene)
{
    return new CCFM56Engine(pScene);
}

//-------------------------------------------------------------------------------------------------

CCFM56Engine::CCFM56Engine(C3DScene* pScene)
    : CJetEngine(pScene)
{
    m_dN1_servo.setPosition(IDLE_N1_NORM);
    m_dN1_servo.setTargetPosition(IDLE_N1_NORM);
}

//-------------------------------------------------------------------------------------------------

CCFM56Engine::~CCFM56Engine()
{
}

//-------------------------------------------------------------------------------------------------

double CCFM56Engine::currentThrust_kg() const
{
    // Only N1 above idle produces thrust
    double dFactor = Angles::clipDouble((m_dN1_servo.position() - IDLE_N1_NORM) / (1.0 - IDLE_N1_NORM), 0.0, 1.0);
    return dFactor * m_dMaxThrust_kg;
}

//-------------------------------------------------------------------------------------------------

void CCFM56Engine::update(double dDeltaTime)
{
    m_dN1_servo.setTargetPosition(IDLE_N1_NORM + (m_dFuelFlow_norm * (1.0 - IDLE_N1_NORM)));
    m_dN1_servo.update(dDeltaTime);

    LOG_VALUE(QString("%1 FF / N1 / THT KG").arg(m_sName),
              QString("%1 / %2 / %3")
              .arg(QString::number(m_dFuelFlow_norm, 'f', 4))
              .arg(QString::number(m_dN1_servo.position(), 'f', 4))
              .arg(QString::number(currentThrust_kg(), 'f', 2))
              );

    CEngine::update(dDeltaTime);
}
