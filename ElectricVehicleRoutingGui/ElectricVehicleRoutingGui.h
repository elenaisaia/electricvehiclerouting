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

    void generateInitialGraph();

    void getChargingstationGraph();

    void nodeClicked(int nodeId);

    class GraphNodeUi;  
    std::unordered_map<unsigned int, GraphNodeUi*> drawnPoints;
    std::deque<unsigned int> usedPoints;
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

    void clearPath();

    class GraphNodeUi : public QGraphicsEllipseItem {
    public:
        GraphNodeUi(ElectricVehicleRoutingGui* mainWindow, int nodeId, qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = nullptr)
            : QGraphicsEllipseItem(x - w / 2, y - h / 2, w, h, parent), mainWindow{ mainWindow }, nodeId{ nodeId }, x{ x }, y{ y } {}
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

        qreal getX() {
            return x;
        }

        qreal getY() {
            return y;
        }

    private:
            ElectricVehicleRoutingGui* mainWindow;
            int nodeId = -1;
            qreal x;
            qreal y;
    };
    
};
