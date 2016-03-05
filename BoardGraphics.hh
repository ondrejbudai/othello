#ifndef GRAPHICS_SCENE_HH
#define GRAPHICS_SCENE_HH

#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QtCore>
#include <iostream>
#include <QResizeEvent>
#include <QPixmap>
#include "MainGame.hh"

namespace othello {
    
    class GraphicsView : public QGraphicsView {
    public:
        GraphicsView(QGraphicsScene* s);   
        virtual void resizeEvent(QResizeEvent*);
    }; 
    
        
    constexpr unsigned GAME_SIZE = 200;

    class BoardGraphics : public QGraphicsScene {
        Q_OBJECT

    signals:

        void ClickSignal(unsigned x, unsigned y);

    public:
        std::vector<std::vector<QGraphicsPixmapItem*>> b;
        unsigned size;

        QPixmap blackDisc;
        QPixmap whiteDisc;
        QPixmap blank;

        BoardGraphics(const std::vector<std::vector<Field>>& logic);
        void repaint();
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);


    private:
        const std::vector<std::vector<Field>>& board_;

        double getPieceSize() const;
    };
}
#endif
