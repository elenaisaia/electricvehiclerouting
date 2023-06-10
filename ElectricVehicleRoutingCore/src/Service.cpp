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

double Service::findCost(unsigned int sourceId, unsigned int destinationId)
{
    timeDijkstra.setSourceId(sourceId);
    timeDijkstra.setDestinationId(destinationId);

    //se adauga sursa in lista de noduri
    auto sourceIntersection = initialGraph.getIntersectionById(sourceId);
    ChargingStation source(sourceIntersection.getId(), sourceIntersection.getX(), sourceIntersection.getY());
    chargingStationGraph.addChargingStationToVertexList(source);

    //se gasesc vecinii sursei si se adauga in lista de noduri
    chargingStationGraph.setAdjacentStations(sourceId, distanceDijkstra.getNextChargingStationsForChargingStation(sourceId));

    //se adauga destinatia in lista de noduri
    auto destinationIntersection = initialGraph.getIntersectionById(sourceId);
    ChargingStation destination(destinationIntersection.getId(), destinationIntersection.getX(), destinationIntersection.getY());
    chargingStationGraph.addChargingStationToVertexList(destination);

    //se gasesc vecinii destinatiei si se adauga in lista de noduri
    //de facut distance dijkstra pe graful transpus pentru setarea arcelor catre destinatie

    return timeDijkstra.findCost();
}
