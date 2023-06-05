#include "ElectricVehicleRoutingGui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    Service service;

    QApplication a(argc, argv);
   
    ElectricVehicleRoutingGui w{ service };
    w.show();

    return a.exec();
}
