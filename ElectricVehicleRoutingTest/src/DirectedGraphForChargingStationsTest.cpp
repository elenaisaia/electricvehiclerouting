#include "DirectedGraphForChargingStationsTest.h"
#include <DirectedGraphForChargingStations.h>
#include <cassert>

void DirectedGraphForChargingStationsTest::runTests()
{
	DirectedGraphForChargingStations graph(5, 6);

	assert(graph.getVertexes() == 5);
	assert(graph.getArches() == 6);
	assert(graph.getVertexList().size() == 0);

	std::unordered_map<unsigned int, ChargingStation> vertexList;

	ChargingStation cs0(0, 100, 0);
	ChargingStation cs1(1, 100, 75);
	ChargingStation cs2(2, 100, 50);
	ChargingStation s(6, 0, 50);
	ChargingStation d(7, 200, 50);

	vertexList[0] = cs0;
	vertexList[1] = cs1;
	vertexList[2] = cs2;
	graph.setVertexList(vertexList);
	assert(graph.getVertexList().size() == 3);

	graph.addChargingStationToVertexList(s);
	graph.addChargingStationToVertexList(d);
	assert(graph.getVertexList().size() == 5);

	assert(graph.getVertexById(1).getId() == 1);
	assert(graph.getVertexById(1).getX() == 100);
	assert(graph.getVertexById(1).getY() == 75);

	assert(graph.getVertexById(7).getId() == 7);
	assert(graph.getVertexById(7).getX() == 200);
	assert(graph.getVertexById(7).getY() == 50);

	std::vector<NextChargingStation> nextChargingStationList;

	NextChargingStation ncs0(cs0, 100, 50, 2, 100);
	NextChargingStation ncs1(cs1, 80, 80, 1, 100);
	NextChargingStation ncs2(cs2, 100, 50, 2, 100);

	nextChargingStationList.push_back(ncs0);
	nextChargingStationList.push_back(ncs1);
	nextChargingStationList.push_back(ncs2);

	graph.setAdjacentStations(s.getId(), nextChargingStationList);
	assert(graph.getAdjacencyList().at(s).size() == 3);
	assert(graph.getAdjacentStations(s).size() == 3);
	assert(graph.getAdjacentStations(d).size() == 0);

	NextChargingStation nc3d(d, 100, 50, 2, 100);
	NextChargingStation nc4d(d, 80, 80, 1, 100);
	NextChargingStation nc5d(d, 100, 50, 2, 100);

	graph.addNextChargingStation(cs0, nc3d);
	assert(graph.getAdjacentStations(cs0).size() == 1);

	graph.addNextChargingStation(cs1, nc4d);
	assert(graph.getAdjacentStations(cs1).size() == 1);

	graph.addNextChargingStation(cs2, nc5d);
	assert(graph.getAdjacentStations(cs2).size() == 1);
}
