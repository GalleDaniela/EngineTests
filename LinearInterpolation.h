#pragma once
#include <vector>

class LinearInterpolation
{
public:
	LinearInterpolation(std::vector<std::pair<double, double>>& iaInterpolationPoints);
	double Interpolate(double iPoint) const;

private:
	std::vector<std::pair<double, double>>& m_aInterpolationPoints;
};

