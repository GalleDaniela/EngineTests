#include "LinearInterpolation.h"

LinearInterpolation::LinearInterpolation(std::vector<std::pair<double, double>>& iaInterpolationPoints)
    : m_aInterpolationPoints(iaInterpolationPoints)
{
}

double LinearInterpolation::Interpolate(double iPoint) const
{
    if (m_aInterpolationPoints.size() < 2)
        return 0.0;

    size_t idx = 0;
    for (; idx < m_aInterpolationPoints.size() - 1; ++idx) {
        if (m_aInterpolationPoints[idx].first <= iPoint && m_aInterpolationPoints[idx + 1].first > iPoint)
            break;
    }

    if (idx >= m_aInterpolationPoints.size() - 1)
        return 0.0;

    double x_1 = m_aInterpolationPoints[idx].first;
    double y_1 = m_aInterpolationPoints[idx].second;
    double x_2 = m_aInterpolationPoints[idx + 1].first;
    double y_2 = m_aInterpolationPoints[idx + 1].second;

    return ((iPoint - x_1) * (y_2 - y_1) / (x_2 - x_1)) + y_1;
}
