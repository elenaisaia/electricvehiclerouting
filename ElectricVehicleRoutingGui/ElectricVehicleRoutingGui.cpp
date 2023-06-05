#include "ElectricVehicleRoutingGui.h"

ElectricVehicleRoutingGui::ElectricVehicleRoutingGui(Service& service, QWidget *parent)
    : QMainWindow(parent), service(service)
{
    ui.setupUi(this);
}

ElectricVehicleRoutingGui::~ElectricVehicleRoutingGui()
{}
