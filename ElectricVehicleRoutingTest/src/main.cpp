#include "ElectricVehicleTest.h"
#include <IntersectionTest.h>
#include <ChargingStationTest.h>
#include <NextChargingStationTest.h>
#include <DirectedGraphForIntersectionsTest.h>

//DirectedGraphForChargingStations readSmallGraphFromFile() {
//    std::ifstream fin("smallgraph.txt");
//    unsigned int v, a;
//    fin >> v >> a;
//
//    DirectedGraphForChargingStations graph = DirectedGraphForChargingStations(v, a);
//
//    /*unsigned int id;
//    int x, y, nrOfChargerTypes, nrOfChargingTimes;
//    for (int i = 0; i < v; i++) {
//        fin >> id >> x >> y >> nrOfChargingTimes >> nrOfChargerTypes;
//
//        ChargingStation chargingStation(id, x, y);
//
//        ChargingTime chargingTime;
//        for (int j = 0; j < nrOfChargingTimes; j++) {
//            fin >> chargingTime.lowLimit >> chargingTime.highLimit >> chargingTime.onePercentChargingTime;
//            chargingStation.addChargingTime(chargingTime);
//        }
//
//        std::string type;
//        for (int j = 0; j < nrOfChargerTypes; j++) {
//            fin >> type;
//            if (type == "Normal")
//                chargingStation.addChargerType(Normal);
//            else if (type == "Fast")
//                chargingStation.addChargerType(Fast);
//            else if (type == "Slow")
//                chargingStation.addChargerType(Slow);
//        }
//        graph.addChargingStationToVertexList(chargingStation);
//    }
//
//    std::unordered_map<unsigned int, ChargingStation> vertexes = graph.getVertexList();
//    unsigned int v1, v2, maxi, avg;
//    for (int i = 0; i < a; i++) {
//        fin >> v1 >> v2 >> maxi >> avg;
//        ChargingStation source = vertexes[v1];
//        ChargingStation destination = vertexes[v2];
//        NextChargingStation station = NextChargingStation::createFromCoordinates(destination, avg, source.getX(), source.getY());
//        graph.addNextChargingStation(source, station);
//    }*/
//
//    return graph;
//}
//
//int main() {
//    ElectricVehicle vehicle(49, Normal, 75, 0.06);
//    vehicle.addCost(0, 30, 20);
//    vehicle.addCost(31, 60, 15);
//    vehicle.addCost(61, 80, 20);
//    vehicle.addCost(81, 100, 35);
//    vehicle.addCost(101, 130, 50);
//
//    //DirectedGraphForChargingStations graph = readSmallGraphFromFile();
//
//    //    std::cout << graph.getVertexes() << " " << graph.getArches() << "\n";
//    //    for(auto &station : graph.getVertexList()) {
//    //        std::cout << station.first << " " << station.second.getId() << " " << station.second.getX() << " " << station.second.getY() << " " << station.second.getOnePercentChargingTime() << "\n";
//    //    }
//    //
//    //    for(const auto& arch : graph.getAdjacencyList()) {
//    //        std::cout << "\n" << arch.first.getId() << ":\n";
//    //        for(auto &station : arch.second) {
//    //            std::cout << station.getChargingStation().getId() << " " << station.getDistance() << " " << station.getAvgSpeed() << " " << station.getTime() << "\n";
//    //        }
//    //    }
//    //    std::cout << "\n";
//
//    /*OptimalTimeDijkstra dijkstra(vehicle, graph, 0, 100);
//    std::cout << dijkstra.findCost() << "\n\n\n";*/
//
//
//    //DirectedGraphForIntersections graph2 = DirectedGraphForIntersections::generateGraph(5, 25, 200, "generatedgraph.txt");
//    DirectedGraphForIntersections graph2 = DirectedGraphForIntersections::readGraphFromFile("generatedgraph.txt");
//    //    std::cout << graph2.getVertexes() << " " << graph2.getArches() << " " << graph2.getMaxDistance() << "\n";
//    //    for(auto &station : graph2.getChargingStationList()) {
//    //        std::cout << station.first << " " << station.second.getId() << " " << station.second.getX() << " " << station.second.getY() << " " << station.second.getOnePercentChargingTime() << "\n";
//    //    }
//    //
//    //    for(auto &station : graph2.getIntersectionList()) {
//    //        std::cout << station.first << " " << station.second.getId() << " " << station.second.getX() << " " << station.second.getY() << "\n";
//    //    }
//    //
//    /*for (const auto& arch : graph2.getAdjacencyList()) {
//        std::cout << "\n" << arch.first << ":\n";
//        for (auto& station : arch.second) {
//            std::cout << station.nextId << " " << station.distance << " " << station.speed << "\n";
//        }
//    }
//    std::cout << "\n";*/
//
//    ShortestDistanceDijkstra dijkstraTransformation(graph2);
//    DirectedGraphForChargingStations graphTransformed(graph2.getVertexes(), 0);
//    graphTransformed.setVertexList(graph2.getChargingStationList());
//
//    std::cout << graphTransformed.getVertexes() << " " << graphTransformed.getArches() << "\n";
//    for (auto& station : graphTransformed.getVertexList()) {
//        std::cout << station.first << " " << station.second.getId() << " " << station.second.getX() << " " << station.second.getY() << " " << "\n";
//    }
//
//    for (auto& vertex : graph2.getChargingStationList()) {
//        std::cout << vertex.first << ":\n";
//        graphTransformed.setAdjacentStations(vertex.first, dijkstraTransformation.getNextChargingStationsForChargingStation(vertex.first));
//        std::cout << vertex.first << " " << graphTransformed.getAdjacentStations(graphTransformed.getVertexList().at(vertex.first)).size() << "\n";
//    }
//
//    for (const auto& arch : graphTransformed.getAdjacencyList()) {
//        std::cout << "\n" << arch.first.getId() << ":\n";
//        for (auto& station : arch.second) {
//            std::cout << station.getChargingStation().getId() << " " << station.getDistance() << " " << station.getAvgSpeed() << " " << station.getTime() << "\n";
//        }
//    }
//    std::cout << "\n";
//
//    OptimalTimeDijkstra dijkstra2(vehicle, graphTransformed, 1, 0);
//    std::cout << dijkstra2.findCost() << "\n\n\n";
//
//    return 0;
//}

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

	return 0;
}