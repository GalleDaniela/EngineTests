#pragma once
#include <memory>
#include "Engine.h"

class ITestStand
{
public:
	ITestStand(const std::shared_ptr<IEngine>& ipEngine);
	void Reset();
	void Start();

protected:
	virtual void CheckStopCondition() = 0;
	virtual void PrintRunInfo();
	virtual void PrintTestName();
	virtual void UpdateStandState();

protected:
	std::shared_ptr<IEngine> m_pEngine{ nullptr };
	double m_timeStep{ 0.01 };
	double m_timeFromStart{ 0.0 };
	double m_maxTimeFromStart{ 2000.0 };

	bool m_stopConditionTriggered{ false };
};

class HeatingTestStand : public ITestStand
{
public:
	HeatingTestStand(const std::shared_ptr<IEngine>& ipEngine);

protected:
	void CheckStopCondition() override;
	void PrintRunInfo() override;
	void PrintTestName() override;
};

class MaxPowerTestStand : public ITestStand
{
public:
	MaxPowerTestStand(const std::shared_ptr<IEngine>& ipEngine);

protected:
	void CheckStopCondition() override;
	void PrintRunInfo() override;
	void PrintTestName() override;
	void UpdateStandState() override;

private:
	double m_maxN{};
	double m_VOfMaxN{};
	double m_prevV{};
	static constexpr double SPINNING_STOP_TOLERANCE{ 0.0001 };
};

