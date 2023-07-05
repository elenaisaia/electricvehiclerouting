#include "Service.h"

#include <fstream>
#include "ChargingStation.h"
#include "NextChargingStation.h"
#include "OptimalTimeDijkstra.h"
#include "DirectedGraphForIntersections.h"
#include "ShortestDistanceDijkstra.h"

void Service::readVehicleFromFile(std::string filename)
{
    std::ifstream fin(filename);
    unsigned int id, batteryPercentage;
    double onePercentChargingTime;
    std::string type;
    int noOfCosts;

    fin >> id >> type >> batteryPercentage >> onePercentChargingTime >> noOfCosts;

    ChargerType chargerType = Normal;
    if (type == "Slow") {
        chargerType = Slow;
    }
    else if (type == "Fast") {
        chargerType = Fast;
    }

    vehicle = ElectricVehicle(id, chargerType, batteryPercentage, onePercentChargingTime);
    for (int i = 0; i < noOfCosts; i++) {
        unsigned int mini, maxi;
        double cost;
        fin >> mini >> maxi >> cost;
        vehicle.addCost(mini, maxi, cost);
    }
}

ElectricVehicle& Service::getVehicle()
{
    return vehicle;
}

DirectedGraphForIntersections& Service::getInitialGraph(std::string filename)
{
    initialGraph = DirectedGraphForIntersections::readGraphFromFile(filename);
    return initialGraph;
}

DirectedGraphForIntersections& Service::generateInitialGraph(unsigned int noOfChargingStations, unsigned int noOfIntersections, double maxDistance, std::string filename)
{
    initialGraph = DirectedGraphForIntersections::generateGraph(noOfChargingStations, noOfIntersections, maxDistance, filename);
    return initialGraph;
}

void Service::initChargingStationGraph()
{
    chargingStationGraph.setVertexList(initialGraph.getChargingStationList());

    for (auto& station : chargingStationGraph.getVertexList()) {
        chargingStationGraph.setAdjacentStations(station.first, distanceDijkstra.getNextChargingStationsForChargingStation(station.first));
    }
}

DirectedGraphForChargingStations& Service::getChargingStationGraph()
{
    return chargingStationGraph;
}

OptimalRoute Service::findPath(unsigned int sourceId, unsigned int destinationId)
{
    timeDijkstra.setSourceId(sourceId);
    timeDijkstra.setDestinationId(destinationId);

    //se adauga sursa in lista de noduri daca este cazul (daca nu e statie de incarcare)
    if (!initialGraph.containsChargingStation(sourceId)) {
        auto sourceIntersection = initialGraph.getIntersectionById(sourceId);
        ChargingStation source(sourceIntersection.getId(), sourceIntersection.getX(), sourceIntersection.getY());
        chargingStationGraph.addChargingStationToVertexList(source);

        //se gasesc vecinii sursei si se adauga in lista de noduri
        chargingStationGraph.setAdjacentStations(sourceId, distanceDijkstra.getNextChargingStationsForChargingStation(sourceId));
    }

    //se adauga destinatia in lista de noduri daca este cazul (daca nu e statie de incarcare)
    if (!initialGraph.containsChargingStation(destinationId)) {
        auto destinationIntersection = initialGraph.getIntersectionById(destinationId);
        ChargingStation destination(destinationIntersection.getId(), destinationIntersection.getX(), destinationIntersection.getY());
        chargingStationGraph.addChargingStationToVertexList(destination);

        //se gasesc vecinii destinatiei si se adauga in lista de noduri
        //se face distance dijkstra pe graful transpus pentru setarea arcelor catre destinatie
        DirectedGraphForIntersections transposedGraph = initialGraph.getTransposedGraph();
        ShortestDistanceDijkstra transposedDijkstra(transposedGraph);
        auto nodes = transposedDijkstra.getNextChargingStationsForChargingStation(destinationId);
        for (auto& node : nodes) {
            NextChargingStation next(destination, node.getDistance(), node.getAvgSpeed(), node.getTime(), 100);
            chargingStationGraph.addNextChargingStation(node.getChargingStation(), next);
        }
    }

    OptimalRoute chargingStationRoute = timeDijkstra.findCost();

    OptimalRoute completeRoute;

    if (chargingStationRoute.path[0] != -1) {
        completeRoute.stoppingPoints = chargingStationRoute.stoppingPoints;
        for (int i = 0; i < chargingStationRoute.path.size() - 1; i++) {
            auto route = distanceDijkstra.getShortestPath(chargingStationRoute.path[i], chargingStationRoute.path[i + 1]);
            for (auto elem : route) {
                completeRoute.path.push_back(elem);
            }
            completeRoute.path.pop_back();
        }
        completeRoute.path.push_back(chargingStationRoute.path[chargingStationRoute.path.size() - 1]);
    }
    else {
        completeRoute.path.push_back(-1);
    }

    return completeRoute;
}
