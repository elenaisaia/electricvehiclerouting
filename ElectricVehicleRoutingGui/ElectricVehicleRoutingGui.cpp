#include "ElectricVehicleRoutingGui.h"



ElectricVehicleRoutingGui::ElectricVehicleRoutingGui(Service& service, QWidget *parent)
    : QMainWindow(parent), service{ service }
{
    ui.setupUi(this);

    mapScene = new QGraphicsScene(this);
    mapView = findChild<QGraphicsView*>("mapView");

    if (mapView) {
        QBrush greenBrush(Qt::green);
        QPen outlinePen(Qt::black);
        
        mapView->setScene(mapScene);
    }

    getInitialGraph();

    qInfo() << "DRAWN POINTS:" << drawnPoints.size();

}

ElectricVehicleRoutingGui::~ElectricVehicleRoutingGui()
{}

//void ElectricVehicleRoutingGui::paintEvent(QPaintEvent * event)
//{
//    /*QPainter painter(this);
//    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::FlatCap));*/
//
//    /*DirectedGraphForIntersections& g = service.getInitialGraph("smallgraph.txt");
//    for (auto& list : g.getAdjacencyList()) {
//        ChargingStation ch1 = g.getChargingStationById(list.first);
//        const int x1 = ch1.getX();
//        const int y1 = ch1.getY();
//        for (auto& arch : list.second) {
//            ChargingStation ch2 = g.getChargingStationById(arch.nextId);
//            const int x2 = ch2.getX();
//            const int y2 = ch2.getY();
//            painter.drawLine(x1, y1, x2, y2);
//        }
//    }*/
//    /*painter.drawLine(0, 0, 200, 200);
//
//    painter.drawLine(10, 0, 210, 200);
//
//    painter.setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::FlatCap));
//    painter.drawLine(10, 0, 210, 200);*/
//}

void ElectricVehicleRoutingGui::on_changeButton_clicked()
{
    qInfo() << "Changing nodes";
    clearSelectedNodes();
    enableAllGraphNodeUi();
}


void ElectricVehicleRoutingGui::on_generateButton_clicked()
{

}



void ElectricVehicleRoutingGui::getInitialGraph()
{
    

    DirectedGraphForIntersections& g = service.getInitialGraph("generatedgraph.txt");
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
                    point1->setBrush(Qt::darkGreen);
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
                    point2->setBrush(Qt::darkGreen);
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
    /*QPen outlinePen(Qt::green);
    mapScene->addLine(-53, -217, -69, -66, outlinePen);
    mapScene->addLine(-69, -66, -100, 7, outlinePen);
    mapScene->addLine(-100, 7, 10, 103, outlinePen);
    mapScene->addLine(10, 103, 90, 92, outlinePen);
    mapScene->addLine(90, 92, 37, 214, outlinePen);*/
}

