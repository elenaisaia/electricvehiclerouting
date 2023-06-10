#include "ChargingStationTest.h"
#include <ChargingStation.h>
#include <cassert>

void ChargingStationTest::runTests()
{
	ChargingStation chargingStation(1, 10, 100);

	assert(chargingStation.getId() == 1);
	assert(chargingStation.getX() == 10);
	assert(chargingStation.getY() == 100);

	ElectricVehicle electricVehicle{ 1, Normal, 50, 0.05 };

	chargingStation.addChargerType(Fast);
	assert(chargingStation.isCompatibleWith(electricVehicle) == false);
	assert(chargingStation.getChargerTypes().size() == 1);

	chargingStation.addChargerType(Normal);
	assert(chargingStation.isCompatibleWith(electricVehicle) == true);
	assert(chargingStation.getChargerTypes().size() == 2);
	
	ChargingTime ch1{ 0, 20, 0.01 };
	ChargingTime ch2{ 21, 40, 0.02 };
	ChargingTime ch3{ 41, 60, 0.03 };
	ChargingTime ch4{ 61, 80, 0.04 };
	ChargingTime ch5{ 81, 100, 0.05 };
	
	chargingStation.addChargingTime(ch1);
	assert(chargingStation.getChargingTimes().size() == 1);

	chargingStation.addChargingTime(ch2);
	assert(chargingStation.getChargingTimes().size() == 2);

	chargingStation.addChargingTime(ch3);
	assert(chargingStation.getChargingTimes().size() == 3);

	chargingStation.addChargingTime(ch4);
	assert(chargingStation.getChargingTimes().size() == 4);

	chargingStation.addChargingTime(ch5);
	assert(chargingStation.getChargingTimes().size() == 5);

	assert(chargingStation.getChargingTime(100, 100, 0) == 0);
	assert(chargingStation.getChargingTime(100, 0, 0) == 0);
	assert(abs(chargingStation.getChargingTime(26, 80, 0) - 1.61) < 0.0000001);
	assert(chargingStation.getChargingTime(30, 20, 0) == 0);

	ChargingStation chargingStation1(1, 20, 20);
	assert(chargingStation == chargingStation1);

	ChargingStation chargingStation2(2, 10, 100);
	assert(chargingStation != chargingStation2);
}
