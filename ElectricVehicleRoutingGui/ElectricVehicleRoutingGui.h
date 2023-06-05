#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ElectricVehicleRoutingGui.h"

#include <QPainter>
#include <DirectedGraphForChargingStations.h>
#include <Service.h>

class ElectricVehicleRoutingGui : public QMainWindow
{
    Q_OBJECT

public:
    ElectricVehicleRoutingGui(Service& service, QWidget* parent = nullptr);
    ~ElectricVehicleRoutingGui();

private:
    Ui::ElectricVehicleRoutingGuiClass ui;
    Service& service;

protected:
    void paintEvent(QPaintEvent* event) override
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
        /*painter.drawLine(0, 0, 200, 200);

        painter.drawLine(10, 0, 210, 200);

        painter.setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::FlatCap));
        painter.drawLine(10, 0, 210, 200);*/
    }
};
