#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ElectricVehicleRoutingGui.h"

#include <QPainter>
#include <DirectedGraphForChargingStations.h>
#include <Service.h>
#include <QHBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <qgraphicsview.h>
#include <qgraphicsscene>

#include <qgraphicsitem.h>

class ElectricVehicleRoutingGui : public QMainWindow
{
    Q_OBJECT

public:
    ElectricVehicleRoutingGui(Service& service, QWidget* parent = nullptr);
    ~ElectricVehicleRoutingGui();

    
private slots:
    void on_changeButton_clicked();

    void on_generateButton_clicked();

private:
    Ui::ElectricVehicleRoutingGuiClass ui;
    Service& service;

    QGraphicsScene* mapScene;
    QGraphicsView* mapView;

    void getVehicle();

    void getInitialGraph();

    void getChargingstationGraph();

    void nodeClicked(int nodeId);

    class GraphNodeUi;  
    std::unordered_map<unsigned int, GraphNodeUi*> drawnPoints;
    int sourceId = -1;
    int destinationId = -1;
    bool isSourceChargingStation = false;
    bool isDestinationChargingStation = false;

    bool isSourceSelected();

    bool isDestinationSelected();

    void clearSelectedNodes();

    void enableAllGraphNodeUi();

    void disableAllGraphNodeUi();

    void clearTable();

    class GraphNodeUi : public QGraphicsEllipseItem {
    public:
        explicit GraphNodeUi(ElectricVehicleRoutingGui* mainWindow, int nodeId, qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = nullptr)
            : QGraphicsEllipseItem(x-w/2, y-h/2, w, h, parent), mainWindow{ mainWindow }, nodeId{ nodeId }  {

        }
        ~GraphNodeUi() = default;

        void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
            disableClick();
            mainWindow->nodeClicked(nodeId);
        }

        void disableClick() {
            QGraphicsItem::setEnabled(false);
        }

        void enableClick() {
            QGraphicsItem::setEnabled(true);
        }

    private:
            ElectricVehicleRoutingGui* mainWindow;
            int nodeId = -1;
    };
    
};
