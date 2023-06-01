#include "ElectricVehicleRoutingGui.h"
#include <QtWidgets/QApplication>
#include <FirstClass.h>

int main(int argc, char *argv[])
{
    FirstClass c;
    c.PrintHelloWorld();

    QApplication a(argc, argv);
    ElectricVehicleRoutingGui w;
    w.show();
    return a.exec();
}
