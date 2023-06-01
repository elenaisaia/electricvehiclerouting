#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ElectricVehicleRoutingGui.h"

class ElectricVehicleRoutingGui : public QMainWindow
{
    Q_OBJECT

public:
    ElectricVehicleRoutingGui(QWidget *parent = nullptr);
    ~ElectricVehicleRoutingGui();

private:
    Ui::ElectricVehicleRoutingGuiClass ui;
};
