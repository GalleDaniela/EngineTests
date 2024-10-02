#include "TestStand.h"
#include <iostream>

ITestStand::ITestStand(const std::shared_ptr<IEngine>& ipEngine)
    : m_pEngine(ipEngine)
{
    Reset();
}

void ITestStand::Reset()
{
    if (m_pEngine)
        m_pEngine->Reset();

    m_timeFromStart = 0.0;
    m_stopConditionTriggered = false;
}

void ITestStand::Start()
{
    if (!m_pEngine) {
        std::cerr << "Set up non null engine" << std::endl;
    }

    while (m_timeFromStart <= m_maxTimeFromStart && !m_stopConditionTriggered) {
        m_pEngine->UpdateState(m_timeStep);
        CheckStopCondition();
        UpdateStandState();
        m_timeFromStart += m_timeStep;
    }

    PrintRunInfo();
    Reset();
}

void ITestStand::PrintRunInfo()
{
    PrintTestName();

    if (!m_stopConditionTriggered)
        std::cout << "The stop condition was not reached within " << m_maxTimeFromStart << " seconds. Aborted by overtime." << std::endl;
    else
        std::cout << "Elapsed run time: " << m_timeFromStart << " seconds" << std::endl;
}

void ITestStand::PrintTestName()
{
    std::cout << "TEST: ";
}

void ITestStand::UpdateStandState()
{
}

HeatingTestStand::HeatingTestStand(const std::shared_ptr<IEngine>& ipEngine)
    : ITestStand(ipEngine)
{
}

void HeatingTestStand::CheckStopCondition()
{
    m_stopConditionTriggered = m_pEngine->GetCurrentT() > m_pEngine->GetOverheatingT();
}

void HeatingTestStand::PrintRunInfo()
{
    ITestStand::PrintRunInfo();
    std::cout << "Engine overheated at " << m_timeFromStart << " seconds" << std::endl;
    std::cout << std::endl;
}

void HeatingTestStand::PrintTestName()
{
    std::cout << "Heating Test" << std::endl;
}

MaxPowerTestStand::MaxPowerTestStand(const std::shared_ptr<IEngine>& ipEngine)
    : ITestStand(ipEngine)
{

}

void MaxPowerTestStand::CheckStopCondition()
{
    m_stopConditionTriggered = (std::abs(m_prevV - m_pEngine->GetCurrentV()) < SPINNING_STOP_TOLERANCE);
}

void MaxPowerTestStand::PrintRunInfo()
{
    ITestStand::PrintRunInfo();
    std::cout << "Max N of test run: " << m_maxN << " kW" << std::endl;
    std::cout << "V on max N of test run: " << m_VOfMaxN << " rad/s" << std::endl;
    std::cout << std::endl;
}

void MaxPowerTestStand::PrintTestName()
{
    std::cout << "Max Power Test" << std::endl;
}

void MaxPowerTestStand::UpdateStandState()
{
    m_prevV = m_pEngine->GetCurrentV();

    if (m_maxN < m_pEngine->GetCurrentN()) {
        m_maxN = m_pEngine->GetCurrentN();
        m_VOfMaxN = m_pEngine->GetCurrentV();
    }
}
