#include "ElectricVehicleRoutingGui.h"
#include <QMessageBox>


ElectricVehicleRoutingGui::ElectricVehicleRoutingGui(Service& service, QWidget *parent)
    : QMainWindow(parent), service{ service }
{
    ui.setupUi(this);

    mapScene = new QGraphicsScene(this);
    mapView = findChild<QGraphicsView*>("mapView");

    if (mapView) {        
        mapView->setScene(mapScene);
    }

    getVehicle();
    getInitialGraph();

    qInfo() << "DRAWN POINTS:" << drawnPoints.size();

    getChargingstationGraph();
}

ElectricVehicleRoutingGui::~ElectricVehicleRoutingGui(){}


void ElectricVehicleRoutingGui::on_changeButton_clicked()
{
    qInfo() << "Changing nodes";
    clearTable();
    clearPath();
    clearSelectedNodes();
    enableAllGraphNodeUi();
}


void ElectricVehicleRoutingGui::on_generateButton_clicked()
{
    qInfo() << "Changing map";
    clearTable();
    clearPath();
    clearSelectedNodes();

    //trebuie golit tot si regenerat
    mapScene->clear();
    drawnPoints.clear();
    

    generateInitialGraph();

}



void ElectricVehicleRoutingGui::getVehicle()
{
    service.readVehicleFromFile("vehicle.txt");
}

void ElectricVehicleRoutingGui::getInitialGraph()
{
    DirectedGraphForIntersections& g = service.getInitialGraph("initialgraph.txt");
    for (auto& list : g.getAdjacencyList()) {
        int x1, y1, x2, y2, id1, id2;
        bool isCh1 = false, isCh2 = false;
        if (g.containsChargingStation(list.first)) {
            ChargingStation ch1 = g.getChargingStationById(list.first);
            x1 = ch1.getX();
            y1 = ch1.getY();
            id1 = ch1.getId();
            isCh1 = true;
        }
        else {
            Intersection i1 = g.getIntersectionById(list.first);
            x1 = i1.getX();
            y1 = i1.getY();
            id1 = i1.getId();
            isCh1 = false;
        }
        
        for (auto& arch : list.second) {
            if (g.containsChargingStation(arch.nextId)) {
                ChargingStation ch2 = g.getChargingStationById(arch.nextId);
                x2 = ch2.getX();
                y2 = ch2.getY();
                id2 = ch2.getId();
                isCh2 = true;
            }
            else {
                Intersection i2 = g.getIntersectionById(arch.nextId);
                x2 = i2.getX();
                y2 = i2.getY();
                id2 = i2.getId();
                isCh2 = false;
            }
            
            
            
            if (!drawnPoints[id1]) {
                auto point1 = new GraphNodeUi(this, id1, x1, y1, 10, 10);
                if (isCh1) {
                    point1->setPen(Qt::NoPen);
                    point1->setBrush(Qt::green);
                }
                else {
                    point1->setPen(Qt::NoPen);
                    point1->setBrush(Qt::black);
                }
                mapScene->addItem(point1);
                drawnPoints[id1] = point1;
            }

            if (!drawnPoints[id2]) {
                auto point2 = new GraphNodeUi(this, id2, x2, y2, 10, 10);
                if (isCh2) {
                    point2->setPen(Qt::NoPen);
                    point2->setBrush(Qt::green);
                }
                else {
                    point2->setPen(Qt::NoPen);
                    point2->setBrush(Qt::black);
                }
                mapScene->addItem(point2);
                drawnPoints[id2] = point2;
            }

            mapScene->addLine(x1, y1, x2, y2);
        }
    }
}

void ElectricVehicleRoutingGui::generateInitialGraph()
{
    DirectedGraphForIntersections& g = service.generateInitialGraph(20, 20, 200, "generatedgraph.txt");
    for (auto& list : g.getAdjacencyList()) {
        int x1, y1, x2, y2, id1, id2;
        bool isCh1 = false, isCh2 = false;
        if (g.containsChargingStation(list.first)) {
            ChargingStation ch1 = g.getChargingStationById(list.first);
            x1 = ch1.getX();
            y1 = ch1.getY();
            id1 = ch1.getId();
            isCh1 = true;
        }
        else {
            Intersection i1 = g.getIntersectionById(list.first);
            x1 = i1.getX();
            y1 = i1.getY();
            id1 = i1.getId();
            isCh1 = false;
        }

        for (auto& arch : list.second) {
            if (g.containsChargingStation(arch.nextId)) {
                ChargingStation ch2 = g.getChargingStationById(arch.nextId);
                x2 = ch2.getX();
                y2 = ch2.getY();
                id2 = ch2.getId();
                isCh2 = true;
            }
            else {
                Intersection i2 = g.getIntersectionById(arch.nextId);
                x2 = i2.getX();
                y2 = i2.getY();
                id2 = i2.getId();
                isCh2 = false;
            }



            if (!drawnPoints[id1]) {
                auto point1 = new GraphNodeUi(this, id1, x1, y1, 10, 10);
                if (isCh1) {
                    point1->setPen(Qt::NoPen);
                    point1->setBrush(Qt::green);
                }
                else {
                    point1->setPen(Qt::NoPen);
                    point1->setBrush(Qt::black);
                }
                mapScene->addItem(point1);
                drawnPoints[id1] = point1;
            }

            if (!drawnPoints[id2]) {
                auto point2 = new GraphNodeUi(this, id2, x2, y2, 10, 10);
                if (isCh2) {
                    point2->setPen(Qt::NoPen);
                    point2->setBrush(Qt::green);
                }
                else {
                    point2->setPen(Qt::NoPen);
                    point2->setBrush(Qt::black);
                }
                mapScene->addItem(point2);
                drawnPoints[id2] = point2;
            }

            mapScene->addLine(x1, y1, x2, y2);
        }
    }
}

void ElectricVehicleRoutingGui::getChargingstationGraph()
{
    service.initChargingStationGraph();
}

void ElectricVehicleRoutingGui::nodeClicked(int nodeId)
{
    qInfo() << "Pressed graph node " << nodeId;

    if (!isSourceSelected()) {
        sourceId = nodeId;
        if (drawnPoints[sourceId]->brush() == Qt::green) {
            isSourceChargingStation = true;
        }
        drawnPoints[sourceId]->setBrush(Qt::red);
        return;
    }

    if (!isDestinationSelected()) {
        destinationId = nodeId;
        if (drawnPoints[destinationId]->brush() == Qt::green) {
            isDestinationChargingStation = true;
        }
        drawnPoints[destinationId]->setBrush(Qt::red);
        disableAllGraphNodeUi();

        qInfo() << "Source = " << sourceId << " Destination = " << destinationId;

        // aici apelez Dijkstra din service
        auto route = service.findPath(sourceId, destinationId);
        if(route.path[0] != -1) {
            for (auto& station : route.path) {
                qInfo() << station << "\n";
            }

            usedPoints = route.path;
            int pathSize = route.path.size() - 1;
            for (int i = 0; i < pathSize; i++) {
                QPen outlinePen(Qt::green);
                auto p1 = drawnPoints[route.path[i]];
                auto p2 = drawnPoints[route.path[i + 1]];
                mapScene->addLine(p1->getX(), p1->getY(), p2->getX(), p2->getY(), outlinePen);
                qInfo() << p1->getX() << " " << p1->getY() << " " << p2->getX() << " " << p2->getY() << "\n";
            }

            for (auto point : drawnPoints) {
                qInfo() << point << "\n";
            }

            ui.tableWidget->setRowCount(route.stoppingPoints.size());
            /*int i = 0;
            for (auto& station : route.stoppingPoints) {
                qInfo() << station.id << " " << station.timeBeforeStop << " " << station.batteryPercentageBeforeStop 
                                      << " " << station.timeAfterStop << " " << station.batteryPercentageAfterStop << "\n";
                ui.tableWidget->setItem(i, 0, new QTableWidgetItem("min " + QString::number(station.timeBeforeStop) + ", battery " + QString::number(station.batteryPercentageBeforeStop) + "%"));
                ui.tableWidget->setItem(i, 1, new QTableWidgetItem("min " + QString::number(station.timeAfterStop) + ", battery " + QString::number(station.batteryPercentageAfterStop) + "%"));
                i++;
            }*/

            auto& station = route.stoppingPoints[0];
            qInfo() << station.id << " " << station.timeBeforeStop << " " << station.batteryPercentageBeforeStop
                << " " << station.timeAfterStop << " " << station.batteryPercentageAfterStop << "\n";
            ui.tableWidget->setItem(0, 0, new QTableWidgetItem("-"));
            ui.tableWidget->setItem(0, 1, new QTableWidgetItem("min " + QString::number(int(station.timeAfterStop)) + ", battery " + QString::number(station.batteryPercentageAfterStop) + "%"));

            int routeSize = route.stoppingPoints.size() - 1;
            for (int i = 1; i < routeSize; i++) {
                station = route.stoppingPoints[i];
                qInfo() << station.id << " " << station.timeBeforeStop << " " << station.batteryPercentageBeforeStop
                    << " " << station.timeAfterStop << " " << station.batteryPercentageAfterStop << "\n";
                ui.tableWidget->setItem(i, 0, new QTableWidgetItem("min " + QString::number(int(station.timeBeforeStop)) + ", battery " + QString::number(station.batteryPercentageBeforeStop) + "%"));
                ui.tableWidget->setItem(i, 1, new QTableWidgetItem("min " + QString::number(int(station.timeAfterStop)) + ", battery " + QString::number(station.batteryPercentageAfterStop) + "%"));
                i++;
            }

            station = route.stoppingPoints[routeSize];
            qInfo() << station.id << " " << station.timeBeforeStop << " " << station.batteryPercentageBeforeStop
                << " " << station.timeAfterStop << " " << station.batteryPercentageAfterStop << "\n";
            ui.tableWidget->setItem(routeSize, 0, new QTableWidgetItem("min " + QString::number(int(station.timeBeforeStop)) + ", battery " + QString::number(station.batteryPercentageBeforeStop) + "%"));
            ui.tableWidget->setItem(routeSize, 1, new QTableWidgetItem("-"));

            int time = (int)(station.timeBeforeStop);
            int hours = time / 60;
            int minutes = time % 60;
            ui.plainTextEdit->setPlainText(QString::fromStdString(std::to_string(hours) + "h " + std::to_string(minutes) + "min "));
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("There aren't any available routes! :<");
            msgBox.exec();
        }
    }
}

bool ElectricVehicleRoutingGui::isSourceSelected()
{
    return sourceId != -1;
}

bool ElectricVehicleRoutingGui::isDestinationSelected()
{
    return destinationId != -1;
}

void ElectricVehicleRoutingGui::clearSelectedNodes()
{
    if (sourceId != -1) {
        if (isSourceChargingStation) {
            drawnPoints[sourceId]->setBrush(Qt::green);
        }
        else {
            drawnPoints[sourceId]->setBrush(Qt::black);
        }
        
        isSourceChargingStation = false;
        sourceId = -1;
        
    }
    if (destinationId != -1) {
        if (isDestinationChargingStation) {
            drawnPoints[destinationId]->setBrush(Qt::green);
        }
        else {
            drawnPoints[destinationId]->setBrush(Qt::black);
        }
        
        isDestinationChargingStation = false;
        destinationId = -1;
    }
}

void ElectricVehicleRoutingGui::enableAllGraphNodeUi()
{
    for (auto mapPair : drawnPoints) {
        mapPair.second->enableClick();
    }
}

void ElectricVehicleRoutingGui::disableAllGraphNodeUi()
{
    for (auto mapPair : drawnPoints) {
        mapPair.second->disableClick();
    }
}

void ElectricVehicleRoutingGui::clearTable()
{
    ui.tableWidget->setRowCount(0);
    ui.plainTextEdit->clear();
}

void ElectricVehicleRoutingGui::clearPath()
{
    int dim = usedPoints.size() - 1;
    for (int i = 0; i < dim; i++) {
        auto p1 = drawnPoints[usedPoints[i]];
        auto p2 = drawnPoints[usedPoints[i + 1]];
        mapScene->addLine(p1->getX(), p1->getY(), p2->getX(), p2->getY());
        qInfo() << p1->getX() << " " << p1->getY() << " " << p2->getX() << " " << p2->getY() << "\n";
    }
    usedPoints.clear();
}
