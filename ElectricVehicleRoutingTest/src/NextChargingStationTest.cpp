#include "NextChargingStationTest.h"
#include <NextChargingStation.h>
#include <cassert>

void NextChargingStationTest::runTests()
{
	ChargingStation chargingStation(1, 10, 100);
	NextChargingStation nextChargingStation(chargingStation, 12.34, 35, 1.2, 80);

	assert(nextChargingStation.getChargingStation().getId() == 1);
	assert(nextChargingStation.getDistance() - 12.34 < 0.0001);
	assert(nextChargingStation.getAvgSpeed() == 35);
	assert(nextChargingStation.getTime() - 1.2 < 0.0001);
	assert(nextChargingStation.getMaxBatteryPercent() == 80);

	NextChargingStation nextChargingStation1(chargingStation, 12.34, 35, 1.2, 80);
	assert(nextChargingStation <= nextChargingStation1);
	assert(nextChargingStation >= nextChargingStation1);

	NextChargingStation nextChargingStation2(chargingStation, 12.34, 35, 1.3, 80);
	assert(nextChargingStation < nextChargingStation2);
	assert(nextChargingStation <= nextChargingStation2);
	assert(nextChargingStation2 > nextChargingStation);
	assert(nextChargingStation2 >= nextChargingStation);

	NextChargingStation nextChargingStation3(chargingStation, 12.34, 35, 1.2, 100);
	assert(nextChargingStation < nextChargingStation3);
	assert(nextChargingStation <= nextChargingStation3);
	assert(nextChargingStation3 > nextChargingStation);
	assert(nextChargingStation3 >= nextChargingStation);

	NextChargingStation nextChargingStation4(chargingStation, 12.4, 35, 1.2, 80);
	assert(nextChargingStation < nextChargingStation4);
	assert(nextChargingStation <= nextChargingStation4);
	assert(nextChargingStation4 > nextChargingStation);
	assert(nextChargingStation4 >= nextChargingStation);
}
