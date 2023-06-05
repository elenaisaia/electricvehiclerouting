#include "Service.h"

#include <fstream>
#include "ChargingStation.h"
#include "NextChargingStation.h"
#include "OptimalTimeDijkstra.h"
#include "DirectedGraphForIntersections.h"
#include "ShortestDistanceDijkstra.h"

Service::Service()
{

}

DirectedGraphForChargingStations Service::getGraph()
{
    ElectricVehicle vehicle(49, Normal, 75, 0.06);
    vehicle.addCost(0, 30, 20);
    vehicle.addCost(31, 60, 15);
    vehicle.addCost(61, 80, 20);
    vehicle.addCost(81, 100, 35);
    vehicle.addCost(101, 130, 50);

    DirectedGraphForIntersections initialGraph = DirectedGraphForIntersections::readGraphFromFile("generatedgraph.txt");

    ShortestDistanceDijkstra dijkstraTransformation(initialGraph);

    DirectedGraphForChargingStations transformedGraph(initialGraph.getNoOfChargingStations(), 0);
    transformedGraph.setVertexList(initialGraph.getChargingStationList());

    for (auto& vertex : initialGraph.getChargingStationList()) {
        transformedGraph.setAdjacentStations(vertex.first, dijkstraTransformation.getNextChargingStationsForChargingStation(vertex.first));
    }

    OptimalTimeDijkstra dijkstraFindPath(vehicle, transformedGraph, 1, 0);

    return transformedGraph;
}

DirectedGraphForIntersections& Service::getInitialGraph()
{
    initialGraph = DirectedGraphForIntersections::readGraphFromFile("generatedgraph.txt");
    return initialGraph;
}

