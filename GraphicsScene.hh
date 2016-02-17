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
        void WaitingOnFreezingEnded();
        void TimeToUnfreeze();
    
    signals:
        void Score_Changed(int white, int black);
        void EndOfGame();
   
    private:
        std::vector<std::vector<QGraphicsPixmapItem*>> b;
        MainGame& game_;
        unsigned size;
        QTimer* timer;
        QTimer* freezeTimer;
        QTimer* unfreezeTimer;

        QImage* blackDisc;
        QImage* whiteDisc;
        QImage* blank;
        QImage* blackDiscFrozen;
        QImage* whiteDiscFrozen;
       
        bool canUnfreez = false;

        void repaint();
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
    
    public:
        GraphicsScene(MainGame &gm);
        double getPieceSize() const ;
    };
}
#endif
