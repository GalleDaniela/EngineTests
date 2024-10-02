#include "Engine.h"
#include "LinearInterpolation.h"


IEngine::IEngine(double iAmbientT, double iOverheatingT)
    : m_ambientT(iAmbientT), m_currentT(iAmbientT), m_overheatingT(iOverheatingT)
{
}

void IEngine::Reset()
{
    m_currentT = m_ambientT;
    m_currentV = 0.0;
    m_currentM = 0.0;
}

double IEngine::GetOverheatingT() const
{
    return m_overheatingT;
}

double IEngine::GetCurrentT() const
{
    return m_currentT;
}

double IEngine::GetCurrentV() const
{
    return m_currentV;
}

double IEngine::GetCurrentM() const
{
    return m_currentM;
}

double IEngine::GetCurrentN() const
{
    return m_currentN;
}


InternalCombustionEngine::InternalCombustionEngine(
    double iAmbientT,
    double iI,
    double iOverheatingT,
    double iHm,
    double iHv,
    double iC,
    const std::vector<std::pair<double, double>>& iMVDependency
) : IEngine(iAmbientT, iOverheatingT), m_I(iI), m_Hm(iHm), m_Hv(iHv), m_C(iC), m_MVDependency(iMVDependency)
{
}

void InternalCombustionEngine::UpdateState(double iDeltaTime)
{
    LinearInterpolation interpol(m_MVDependency);
    m_currentM = interpol.Interpolate(m_currentV);

    double heatingRate = m_currentM * m_Hm + m_currentV * m_currentV * m_Hv;
    double coolingRate = m_C * (m_ambientT - m_currentT);
    m_currentT += (heatingRate - coolingRate) * iDeltaTime;
    m_currentN = m_currentM * m_currentV / 1000;

    m_currentV += m_currentM * iDeltaTime / m_I;

}
