#ifndef GRAPHICS_SCENE_HH
#define GRAPHICS_SCENE_HH



#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QtCore>
#include <iostream>
#include <QResizeEvent>
#include "OthelloGui.hh"
#include "MainGame.hh"

namespace othello {
    constexpr unsigned GAME_SIZE = 200;

    class GraphicsScene : public QGraphicsScene {
        Q_OBJECT

    public slots:
        void TickingClocks();
    
    public:
        MainGame game_;
        std::vector<std::vector<QGraphicsRectItem*>> b;
        unsigned size;
        QTimer *timer;

        GraphicsScene();
        void repaint();
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
        double getPieceSize() const ;
        void setSize(QSize s);
    };
}
#endif
