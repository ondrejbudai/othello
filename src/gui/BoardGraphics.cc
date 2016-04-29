#include "BoardGraphics.hh"


namespace othello {
    GraphicsView::GraphicsView(QGraphicsScene* s) : QGraphicsView(s) {
        setMouseTracking(true);
    }

    void GraphicsView::resizeEvent(QResizeEvent*) {
        fitInView(0, 0, GAME_SIZE, GAME_SIZE, Qt::KeepAspectRatio);
        //dynamic_cast<BoardGraphics*>(scene())->setSize(event->size());
    }

    void GraphicsView::mouseMoveEvent(QMouseEvent* mouseEvent) {
        emit mouseMoveSignal(mapToScene(mouseEvent->pos()));
    }

    BoardGraphics::BoardGraphics(const std::vector<std::vector<Field>>& board) : QGraphicsScene{0, 0, GAME_SIZE,
                                                                                                GAME_SIZE},
                                                                                 size{GAME_SIZE}, board_{board} {

        blackDisc = QPixmap::fromImage(QImage("img/blackDisc.jpg"));
        whiteDisc = QPixmap::fromImage(QImage("img/whiteDisc.jpg"));
        blank = QPixmap::fromImage(QImage("img/blank.jpg"));

        const double pieceSize = getPieceSize();
        for (unsigned x = 0; x < board_.size(); ++x) {
            b.emplace_back();
            for (unsigned y = 0; y < board_.size(); ++y) {
                QGraphicsPixmapItem* item = new QGraphicsPixmapItem(blank);
                b[x].push_back(item);
                item->setScale(pieceSize / item->boundingRect().width());
                //item->setPos((board_.size() - 1 - x) * pieceSize, (board_.size() - 1 - y) * pieceSize);
                item->setPos(y * pieceSize, x * pieceSize);
                addItem(item);
            }
        }
        repaint();
    }


    void BoardGraphics::repaint() {
        for (unsigned x = 0; x < board_.size(); ++x) {
            for (unsigned y = 0; y < board_.size(); ++y) {
                auto& piece = b[x][y];
                if (!board_[x][y].occupied_)
                    piece->setPixmap(blank);
                else if (board_[x][y].piece_ == Color::BLACK)
                    piece->setPixmap(blackDisc);
                else
                    piece->setPixmap(whiteDisc);
            }
        }

//        if(mouseOver){
//            b[mouseX][mouseY]->setPixmap(blackDisc);
//        }
    }

    void BoardGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) {
        double mx = mouseEvent->scenePos().x();
        double my = mouseEvent->scenePos().y();

        // TODO: otestuj, jestli je tato podminka dostatecne silna!
        if (mx < 0 || mx > width() || my < 0 || my > height())
            return;

        unsigned x = static_cast<unsigned>(mx / getPieceSize());
        unsigned y = static_cast<unsigned>(my / getPieceSize());

        emit ClickSignal(y, x);
    }

    void BoardGraphics::mouseMoveSlot(QPointF coords) {
        double mx = coords.x();
        double my = coords.y();

        // TODO: otestuj, jestli je tato podminka dostatecne silna!
        if (mx < 0 || mx > width() || my < 0 || my > height())
            return;

        unsigned x = static_cast<unsigned>(mx / getPieceSize());
        unsigned y = static_cast<unsigned>(my / getPieceSize());

        if (x != mouseX || y != mouseY) {
            mouseOver = true;
            mouseX = y;
            mouseY = x;
            repaint();
        }
    }

    double BoardGraphics::getPieceSize() const {
        return static_cast<double>(size) / board_.size();
    }
}


