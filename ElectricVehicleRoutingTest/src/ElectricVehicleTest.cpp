#include "ElectricVehicleTest.h"
#include <ElectricVehicle.h>
#include <cassert>

void ElectricVehicleTest::runTests()
{
	ElectricVehicle electricVehicle{ 1, Normal, 50, 0.05 };
	electricVehicle.addCost(0, 30, 20);
	electricVehicle.addCost(31, 60, 15);
	electricVehicle.addCost(61, 80, 20);
	electricVehicle.addCost(81, 100, 35);
	electricVehicle.addCost(101, 130, 50);

	assert(electricVehicle.getId() == 1);
	assert(electricVehicle.getBatteryPercentage() == 50);
	assert(electricVehicle.getChargerType() == Normal);
	assert(electricVehicle.getCostPerTimeUnit(60) == 15);
	assert(electricVehicle.getCostPerTimeUnit(61) == 20);
	assert(electricVehicle.getCostPerTimeUnit(71) == 20);

	electricVehicle.setBatteryPercentage(25);
	assert(electricVehicle.getBatteryPercentage() == 25);
}
