/**
 * @file
 * @brief Widget na zobrazování herní grafiky.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef GRAPHICS_SCENE_HH
#define GRAPHICS_SCENE_HH

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QResizeEvent>
#include <QPixmap>
#include "../logic/MainGame.hh"

namespace othello {

    class GraphicsView : public QGraphicsView {
    Q_OBJECT
    public:
        GraphicsView(QGraphicsScene* s);

        virtual void resizeEvent(QResizeEvent*);
        virtual void mouseMoveEvent(QMouseEvent* mouseEvent) override;
        virtual void enterEvent(QEvent*) override;
        virtual void leaveEvent(QEvent*) override;

    signals:
        void mouseMoveSignal(QPointF coords);
        void enterSignal();
        void leaveSignal();
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
        QPixmap blackDiscLowOpacity;
        QPixmap whiteDisc;
        QPixmap whiteDiscLowOpacity;
        QPixmap blank;

        BoardGraphics(const MainGame& logic);

        void repaint();

        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

    public slots:
        void mouseMoveSlot(QPointF coords);
        void enterSlot();
        void leaveSlot();

    private:
        const MainGame& board_;

        std::vector<Coords> changes;

        double getPieceSize() const;
        bool mouseOver = false;
    };
}
#endif
