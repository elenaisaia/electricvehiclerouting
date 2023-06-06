#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ElectricVehicleRoutingGui.h"

#include <QPainter>
#include <DirectedGraphForChargingStations.h>
#include <Service.h>
#include <QHBoxLayout>
#include <QTableView>
#include <QPushButton>

class ElectricVehicleRoutingGui : public QMainWindow
{
    Q_OBJECT

public:
    ElectricVehicleRoutingGui(Service& service, QWidget* parent = nullptr);
    ~ElectricVehicleRoutingGui();

    /*void paintEvent(QPaintEvent* event) override;*/

private slots:
    void on_changeButton_clicked();

    void on_generateButton_clicked();

private:
    Ui::ElectricVehicleRoutingGuiClass ui;
    Service& service;

    void getInitialGraph();
};
