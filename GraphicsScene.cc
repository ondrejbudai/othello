#include "GraphicsScene.hh"

namespace othello {
    GraphicsScene::GraphicsScene(const GameBoard& board) : QGraphicsScene{0, 0, GAME_SIZE, GAME_SIZE},
                                                           size{GAME_SIZE}, board_{board} {

        blackDisc = QPixmap::fromImage(QImage("img/blackDisc.jpg"));
        whiteDisc = QPixmap::fromImage(QImage("img/whiteDisc.jpg"));
        blank = QPixmap::fromImage(QImage("img/blank.jpg"));

        const double pieceSize = getPieceSize();
        for (unsigned x = 0; x < board_.getSize(); ++x) {
            b.emplace_back();
            for (unsigned y = 0; y < board_.getSize(); ++y) {
                QGraphicsPixmapItem* item = new QGraphicsPixmapItem(blank);
                b[x].push_back(item);
                item->setScale(pieceSize / item->boundingRect().width());
                item->setPos((board_.getSize() - 1 - x) * pieceSize, (board_.getSize() - 1 - y) * pieceSize);
                item->setPos(x * pieceSize, y * pieceSize);
                addItem(item);
            }
        }
        repaint();
    }


    void GraphicsScene::repaint() {
        for (unsigned x = 0; x < board_.getSize(); ++x) {
            for (unsigned y = 0; y < board_.getSize(); ++y) {
                auto& piece = b[x][y];
                if (!board_.isOccupied(x, y))
                    piece->setPixmap(blank);
                else if (board_.GetColor(x, y) == Color::BLACK)
                    piece->setPixmap(blackDisc);
                else
                    piece->setPixmap(whiteDisc);
            }
        }
    }

    void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) {
        double mx = mouseEvent->scenePos().x();
        double my = mouseEvent->scenePos().y();

        // TODO: otestuj, jestli je tato podminka dostatecne silna!
        if (mx < 0 || mx > width() || my < 0 || my > height())
            return;

        unsigned x = static_cast<unsigned>(mx / getPieceSize());
        unsigned y = static_cast<unsigned>(my / getPieceSize());

        emit ClickSignal(x, y);
    }

    double GraphicsScene::getPieceSize() const {
        return static_cast<double>(size) / board_.getSize();
    }
}


