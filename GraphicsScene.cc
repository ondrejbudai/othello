#include "GraphicsScene.hh"

namespace othello {
        
    GraphicsScene::GraphicsScene() : QGraphicsScene{0, 0, GAME_SIZE, GAME_SIZE}, game_(10, PlayerType::HUMAN, PlayerType::AI),
                      size{GAME_SIZE} {

        
        timer = new QTimer(this);
        timer->setSingleShot(true);

        const GameBoard& board = game_.getLogic().getBoard();
        const double pieceSize = getPieceSize();
        b.reserve(10);
        for (unsigned x = 0; x < board.getSize(); ++x) {
            b[x].reserve(10);
            for (unsigned y = 0; y < board.getSize(); ++y) {
                b[x][y] = addRect(x * pieceSize, y * pieceSize, pieceSize, pieceSize);
            }
        }
        repaint();
        connect(timer,SIGNAL(timeout()), this, SLOT(TickingClocks()));
    }


    void  GraphicsScene::repaint() {
        const GameBoard& board = game_.getLogic().getBoard();
        const double pieceSize = getPieceSize();
        for (unsigned x = 0; x < board.getSize(); ++x) {
            for (unsigned y = 0; y < board.getSize(); ++y) {
                QColor c;
                if (!board.isOccupied(x, y)) {
                    c = {255, 255, 255, 0};
                } else if (board.GetColor(x, y) == Color::BLACK) {
                    c = {0, 0, 0};
                } else {
                    c = {200, 200, 200};
                }
                b[x][y]->setBrush(QBrush(c));
                b[x][y]->setRect(x * pieceSize, y * pieceSize, pieceSize, pieceSize);
            }
        }
    }

    void  GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) {
        if (!game_.getCurrentPlayer().isAi()) {
            game_.event(mouseEvent->scenePos().x() / getPieceSize(), mouseEvent->scenePos().y() / getPieceSize());
            if (game_.getCurrentPlayer().isAi()) {
                this->timer->start(1000);
                //TODO: nastav timer
            }
        }
        repaint();
        QGraphicsScene::mouseReleaseEvent(mouseEvent);
    }

    double  GraphicsScene::getPieceSize() const {
        const GameBoard& board = game_.getLogic().getBoard();
        return double(double(size) / board.getSize());
    }

    void  GraphicsScene::setSize(QSize s) {
        size = s.width() > s.height() ? s.height() : s.width();
        repaint();
    }


    void GraphicsScene::TickingClocks(){
        Player p = game_.getCurrentPlayer();
        Coords c = p.play();
        game_.event(c.GetX(), c.GetY());
        repaint();
    }
}


