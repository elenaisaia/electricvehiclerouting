#include "DirectedGraphForIntersections.h"
#include <fstream>
#include <cmath>
#include <random>

DirectedGraphForIntersections::DirectedGraphForIntersections(double maxDistance, unsigned int vertexes) : vertexes(vertexes), maxDistance(maxDistance), arches(0) {}

unsigned int DirectedGraphForIntersections::getVertexes() const {
    return vertexes;
}

unsigned int DirectedGraphForIntersections::getArches() const {
    return arches;
}

const std::unordered_map<unsigned int, std::vector<NextNode>> &DirectedGraphForIntersections::getAdjacencyList() const {
    return adjacencyList;
}

const std::unordered_map<unsigned int, ChargingStation> &DirectedGraphForIntersections::getChargingStationList() const {
    return chargingStationList;
}

const std::unordered_map<unsigned int, Intersection> &DirectedGraphForIntersections::getIntersectionList() const {
    return intersectionList;
}

void DirectedGraphForIntersections::addChargingStationToChargingStationList(const ChargingStation& chargingStation) {
    chargingStationList[chargingStation.getId()] = chargingStation;
}

void DirectedGraphForIntersections::addIntersectionToIntersectionList(const Intersection& intersection) {
    intersectionList[intersection.getId()] = intersection;
}

void DirectedGraphForIntersections::addToAdjacencyList(unsigned int sourceId, unsigned int destinationId, double distance,
                                                  unsigned int speed) {
    adjacencyList[sourceId].push_back(NextNode{distance, speed, destinationId});
}

std::vector<NextNode> DirectedGraphForIntersections::getAdjacentNodes(unsigned int id) {
    return adjacencyList[id];
}

Intersection DirectedGraphForIntersections::getIntersectionById(unsigned int id) {
    return intersectionList[id];
}

ChargingStation DirectedGraphForIntersections::getChargingStationById(unsigned int id) {
    return chargingStationList[id];
}

bool DirectedGraphForIntersections::containsChargingStation(unsigned int id) {
    if(chargingStationList.find(id) == chargingStationList.end())
        return false;
    return true;
}

double DirectedGraphForIntersections::getMaxDistance() const {
    return maxDistance;
}

DirectedGraphForIntersections DirectedGraphForIntersections::generateGraph(unsigned int noOfChargingStations,
                                                                           unsigned int noOfIntersections,
                                                                           double maxDistance,
                                                                           const std::string& fileName) {
    DirectedGraphForIntersections g(maxDistance, noOfChargingStations + noOfIntersections);

    for(unsigned int i = 0; i < noOfChargingStations; i++) {
        ChargingStation station(i, iRand(-250, 250), iRand(-250, 250));

        int k = 5; //numarul de nivele de incarcare e 5 => avem nivelele 0-20, 21-40, 41-60, 61-80, 81-100 %
        double time = fRand(0.01, 0.05);
        for (int j = 0; j < k; j++) {
            ChargingTime chargingTime{ j * 20 + 1, (j + 1) * 20, time + j * 0.01};
            if (j == 0) {
                chargingTime.lowLimit = 0;
            }
            station.addChargingTime(chargingTime);
        }

        double noOfChargerTypes = fRand(0, 30);
        station.addChargerType(Normal);
        if(noOfChargerTypes > 9) {
            station.addChargerType(Fast);
        }
        if(noOfChargerTypes > 19) {
            station.addChargerType(Slow);
        }

        g.addChargingStationToChargingStationList(station);
    }

    for(unsigned int i = noOfChargingStations; i < noOfIntersections + noOfChargingStations; i++) {
        g.addIntersectionToIntersectionList(Intersection(i, iRand(-250, 250), iRand(-250, 250)));
    }

    g.setArches(0);
    for(unsigned int i = 0; i < noOfChargingStations; i++) {
        for(unsigned int j = 0; j < noOfChargingStations; j++) {
            if(i != j) {
                double distance = euclidean_distance(g.getChargingStationById(i).getX(), g.getChargingStationById(i).getY(),
                                                     g.getChargingStationById(j).getX(), g.getChargingStationById(j).getY()) *
                                  fRand(1, sqrt(2));
                if (distance > 0 && distance < maxDistance &&
                    iRand(0, 99) < 50) { //adding an arch with a p% probability
                    unsigned int speed = iRand(30, 131);
                    speed -= speed % 10;
                    g.addToAdjacencyList(i, j, distance, speed);
                    g.incrementArches();
                }
            }
        }

        for(unsigned int j = noOfChargingStations; j < noOfIntersections + noOfChargingStations; j++) {
            double distance = euclidean_distance(g.getChargingStationById(i).getX(), g.getChargingStationById(i).getY(),
                                                 g.getIntersectionById(j).getX(), g.getIntersectionById(j).getY()) *
                              fRand(1, sqrt(2));
            if (distance > 0 && distance < maxDistance && iRand(0, 99) < 50) { //adding an arch with a p% probability
                unsigned int speed = iRand(30, 131);
                speed -= speed % 10;
                g.addToAdjacencyList(i, j, distance, speed);
                g.incrementArches();
            }
        }
    }

    for(unsigned int i = noOfChargingStations; i < noOfIntersections + noOfChargingStations; i++) {
        for(unsigned int j = 0; j < noOfChargingStations; j++) {
            double distance = euclidean_distance(g.getIntersectionById(i).getX(), g.getIntersectionById(i).getY(),
                                                 g.getChargingStationById(j).getX(), g.getChargingStationById(j).getY()) *
                              fRand(1, sqrt(2));
            if (distance > 0 && distance < maxDistance && iRand(0, 99) < 50) { //adding an arch with a p% probability
                unsigned int speed = iRand(30, 131);
                speed -= speed % 10;
                g.addToAdjacencyList(i, j, distance, speed);
                g.incrementArches();
            }
        }

        for(unsigned int j = noOfChargingStations; j < noOfIntersections + noOfChargingStations; j++) {
            if(i != j) {
                double distance = euclidean_distance(g.getIntersectionById(i).getX(), g.getIntersectionById(i).getY(),
                                                     g.getIntersectionById(j).getX(), g.getIntersectionById(j).getY()) *
                                  fRand(1, sqrt(2));
                if (distance > 0 && distance < maxDistance &&
                    iRand(0, 99) < 50) { //adding an arch with a p% probability
                    unsigned int speed = iRand(30, 131);
                    speed -= speed % 10;
                    g.addToAdjacencyList(i, j, distance, speed);
                    g.incrementArches();
                }
            }
        }
    }

    g.writeGraphToFile(fileName);
    return g;
}

DirectedGraphForIntersections DirectedGraphForIntersections::readGraphFromFile(const std::string& fileName) {
    std::ifstream fin(fileName);

    unsigned int noOfChargingStations, noOfIntersections, noOfArches;
    double maxDistance;
    fin >> noOfChargingStations >> noOfIntersections >> noOfArches >> maxDistance;

    DirectedGraphForIntersections g(maxDistance, noOfIntersections + noOfChargingStations);
    g.setArches(noOfArches);

    for(int i = 0; i < noOfChargingStations; i++) {
        unsigned int id, noOfChargingTypes, noOfChargingTimes;
        int x, y;
        fin >> id >> x >> y >> noOfChargingTimes >> noOfChargingTypes;

        ChargingStation chargingStation(id, x, y);

        for (int j = 0; j < noOfChargingTimes; j++) {
            ChargingTime chargingTime;
            fin >> chargingTime.lowLimit >> chargingTime.highLimit >> chargingTime.onePercentChargingTime;
            chargingStation.addChargingTime(chargingTime);
        }

        for (int j = 0; j < noOfChargingTypes; j++) {
            std::string type;
            fin >> type;
            if(type == "Normal") {
                chargingStation.addChargerType(Normal);
            }
            else if (type == "Fast") {
                chargingStation.addChargerType(Fast);
            }
            else if (type == "Slow") {
                chargingStation.addChargerType(Slow);
            }
        }

        g.addChargingStationToChargingStationList(chargingStation);
    }

    for(int i = 0; i < noOfIntersections; i++) {
        unsigned int id;
        int x, y;
        fin >> id >> x >> y;

        g.addIntersectionToIntersectionList(Intersection(id, x, y));
    }

    for(int i = 0; i < noOfArches; i++) {
        unsigned int sourceId, destinationId, speed;
        double distance;
        fin >> sourceId >> destinationId >> distance >> speed;

        g.addToAdjacencyList(sourceId, destinationId, distance, speed);
    }

    return g;
}

void DirectedGraphForIntersections::writeGraphToFile(const std::string& fileName) const {
    std::ofstream fout(fileName);

    fout << chargingStationList.size() << " " << intersectionList.size() << " " << arches << " " << maxDistance << "\n";

    for (auto& chargingStation : chargingStationList) {
        auto& types = chargingStation.second.getChargerTypes();
        auto& times = chargingStation.second.getChargingTimes();
        fout << chargingStation.first << " " << chargingStation.second.getX() << " " << chargingStation.second.getY()
            << " " << times.size() << " " << types.size() << "\n";

        for (auto& time : times) {
            fout << time.lowLimit << " " << time.highLimit << " " << time.onePercentChargingTime << "\n";
        }

        for (auto& type : types) {
            if(type == Normal) {
                fout << "Normal\n";
            }
            else if(type == Fast) {
                fout << "Fast\n";
            }
            else {
                fout << "Slow\n";
            }
        }
    }

    for(auto& intersection : intersectionList) {
        fout << intersection.first << " " << intersection.second.getX() << " " << intersection.second.getY() << "\n";
    }

    for(auto& arch : adjacencyList) {
        for(auto& next : arch.second) {
            fout << arch.first << " " << next.nextId << " " << next.distance << " " << next.speed << "\n";
        }
    }
}

double DirectedGraphForIntersections::euclidean_distance(int x, int y, unsigned int x1, unsigned int y1) {
    return sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
}

double DirectedGraphForIntersections::fRand(double fMin, double fMax) {
//    double f = (double)rand() / RAND_MAX;
//    return fMin + f * (fMax - fMin);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(fMin, fMax);
    return dist(mt);
}

int DirectedGraphForIntersections::iRand(int iMin, int iMax) {
//    int i = (int)rand() / RAND_MAX;
//    return iMin + i * (iMax - iMin);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(iMin, iMax);
    return (int)dist(mt);
}

void DirectedGraphForIntersections::setArches(unsigned int arches) {
    DirectedGraphForIntersections::arches = arches;
}

void DirectedGraphForIntersections::incrementArches() {
    arches++;
}

unsigned int DirectedGraphForIntersections::getNoOfChargingStations()
{
    return chargingStationList.size();
}

bool NextNode::operator<(const NextNode &rhs) const {
    if (distance < rhs.distance)
        return true;
    if (rhs.distance < distance)
        return false;
    if (speed > rhs.speed)
        return true;
    if (rhs.speed > speed)
        return false;
    return nextId < rhs.nextId;
}

bool NextNode::operator>(const NextNode &rhs) const {
    return rhs < *this;
}

bool NextNode::operator<=(const NextNode &rhs) const {
    return !(rhs < *this);
}

bool NextNode::operator>=(const NextNode &rhs) const {
    return !(*this < rhs);
}
