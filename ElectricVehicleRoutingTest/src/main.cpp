#include "ElectricVehicleTest.h"
#include <IntersectionTest.h>
#include <ChargingStationTest.h>
#include <NextChargingStationTest.h>
#include <DirectedGraphForIntersectionsTest.h>
#include <DirectedGraphForChargingStationsTest.h>
#include <ShortestDistanceDijkstraTest.h>
#include <OptimalTimeDijkstraTest.h>
#include <ServiceTest.h>

int main()
{
	ElectricVehicleTest electricVehicleTest;
	electricVehicleTest.runTests();

	IntersectionTest intersectionTest;
	intersectionTest.runTests();

	ChargingStationTest chargingStationTest;
	chargingStationTest.runTests();

	NextChargingStationTest nextChargingStationTest;
	nextChargingStationTest.runTests();

	DirectedGraphForIntersectionsTest directedGraphForIntersectionsTest;
	directedGraphForIntersectionsTest.runTests();

	DirectedGraphForChargingStationsTest directedGraphForChargingStationsTest;
	directedGraphForChargingStationsTest.runTests();

	ShortestDistanceDijkstraTest shortestDistanceDijkstraTest;
	shortestDistanceDijkstraTest.runTests();

	OptimalTimeDijkstraTest optimalTimeDijkstraTest;
	optimalTimeDijkstraTest.runTests();

	ServiceTest serviceTest;
	serviceTest.runTests();

	return 0;
}