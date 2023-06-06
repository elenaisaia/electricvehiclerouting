#include "ElectricVehicleRoutingGui.h"

ElectricVehicleRoutingGui::ElectricVehicleRoutingGui(Service& service, QWidget *parent)
    : QMainWindow(parent), service{ service }
{
    ui.setupUi(this);
}

ElectricVehicleRoutingGui::~ElectricVehicleRoutingGui()
{}

//void ElectricVehicleRoutingGui::paintEvent(QPaintEvent * event)
//{
//    QPainter painter(this);
//    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::FlatCap));
//
//    DirectedGraphForIntersections& g = service.getInitialGraph();
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
//    }
//    ///*painter.drawLine(0, 0, 200, 200);
//
//    //painter.drawLine(10, 0, 210, 200);
//
//    //painter.setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::FlatCap));
//    //painter.drawLine(10, 0, 210, 200);*/
//}

void ElectricVehicleRoutingGui::on_changeButton_clicked()
{
    getInitialGraph();
}


void ElectricVehicleRoutingGui::on_generateButton_clicked()
{

}

void ElectricVehicleRoutingGui::getInitialGraph()
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::FlatCap));

    DirectedGraphForIntersections& g = service.getInitialGraph();
    for (auto& list : g.getAdjacencyList()) {
        ChargingStation ch1 = g.getChargingStationById(list.first);
        const int x1 = ch1.getX();
        const int y1 = ch1.getY();
        for (auto& arch : list.second) {
            ChargingStation ch2 = g.getChargingStationById(arch.nextId);
            const int x2 = ch2.getX();
            const int y2 = ch2.getY();
            painter.drawLine(x1, y1, x2, y2);
        }
    }
}

