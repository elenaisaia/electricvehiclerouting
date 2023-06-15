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

    //void paintEvent(QPaintEvent* event) override;

    
private slots:
    void on_changeButton_clicked();

    void on_generateButton_clicked();

private:
    Ui::ElectricVehicleRoutingGuiClass ui;
    Service& service;

    QGraphicsScene* mapScene;
    QGraphicsView* mapView;

    void getInitialGraph();

    void nodeClicked(int nodeId) {
        qInfo() << "Pressed graph node " << nodeId;

        if (!isSourceSelected()) {
            sourceId = nodeId;
            return;
        }

        if (!isDestinationSelected()) {
            destinationId = nodeId;
            disableAllGraphNodeUi();

            // aici apelez Dijkstra din service
            qInfo() << "Source = " << sourceId << " Destination = " << destinationId;
        }

    }

    class GraphNodeUi;  
    std::unordered_map<unsigned int, GraphNodeUi*> drawnPoints;
    int sourceId = -1;
    int destinationId = -1;

    bool isSourceSelected() {
        return sourceId != -1;
    }

    bool isDestinationSelected() {
        return destinationId != -1;
    }

    void clearSelectedNodes() {
        sourceId = -1;
        destinationId = -1;
    }

    void enableAllGraphNodeUi() {
        for (auto mapPair : drawnPoints) {
            mapPair.second->enableClick();
        }
    }

    void disableAllGraphNodeUi() {
        for (auto mapPair : drawnPoints) {
            mapPair.second->disableClick();
        }
    }

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
