#ifndef GRAPHICS_SCENE_HH
#define GRAPHICS_SCENE_HH

#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QtCore>
#include <iostream>
#include <QResizeEvent>
#include <QPixmap>
#include "MainGame.hh"

namespace othello {
    constexpr unsigned GAME_SIZE = 200;

    class GraphicsScene : public QGraphicsScene {
        Q_OBJECT

    signals:

        void ClickSignal(unsigned x, unsigned y);

    public:
        std::vector<std::vector<QGraphicsPixmapItem*>> b;
        unsigned size;

        QPixmap blackDisc;
        QPixmap whiteDisc;
        QPixmap blank;

        GraphicsScene(const GameBoard& logic);
        void repaint();
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);


    private:
        const GameBoard& board_;

        double getPieceSize() const;
    };
}
#endif
