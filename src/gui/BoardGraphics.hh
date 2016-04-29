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
#include "../logic/MainGame.hh"

namespace othello {

    class GraphicsView : public QGraphicsView {
    Q_OBJECT
    public:
        GraphicsView(QGraphicsScene* s);

        virtual void resizeEvent(QResizeEvent*);

        virtual void mouseMoveEvent(QMouseEvent* mouseEvent);

    signals:
        void mouseMoveSignal(QPointF coords);
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

    public slots:
        void mouseMoveSlot(QPointF coords);

    private:
        const std::vector<std::vector<Field>>& board_;

        double getPieceSize() const;

        unsigned int mouseX;
        unsigned int mouseY;
        bool mouseOver = false;
    };
}
#endif
