#pragma once

#include <iostream>
#include "Engine.h"
#include "TestStand.h"

int main()
{
	double ambientT{};

	std::cout << "Input ambient temperature(Celsius)" << std::endl;
	std::cin >> ambientT;

	auto pEngine = std::make_shared<InternalCombustionEngine>(ambientT, 10.0, 150.0, 0.01, 0.0001, 0.1, std::vector<std::pair<double, double>>{ { 0, 20 }, { 75, 75 }, { 150, 10 }, { 200, 105 }, { 250, 75 }, { 300, 0 } });

	HeatingTestStand heatingTestStand(pEngine);
	MaxPowerTestStand maxPowerTestStand(pEngine);

	heatingTestStand.Start();
	maxPowerTestStand.Start();
}