/**
 * @file
 * @brief Widget na zobrazování herní grafiky.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

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

    void GraphicsView::enterEvent(QEvent*){
        emit enterSignal();
    }

    void GraphicsView::leaveEvent(QEvent*){
        emit leaveSignal();
    }

    BoardGraphics::BoardGraphics(const MainGame& board) : QGraphicsScene{0, 0, GAME_SIZE,
                                                                                                GAME_SIZE},
                                                                                 size{GAME_SIZE}, board_{board} {

        blackDisc = QPixmap::fromImage(QImage("img/blackDisc.jpg"));
        blackDiscLowOpacity = QPixmap::fromImage(QImage("img/blackLowOpacity.png"));
        whiteDisc = QPixmap::fromImage(QImage("img/whiteDisc.jpg"));
        whiteDiscLowOpacity = QPixmap::fromImage(QImage("img/whiteLowOpacity.png"));
        blank = QPixmap::fromImage(QImage("img/blank.jpg"));

        const double pieceSize = getPieceSize();
        for (unsigned x = 0; x < board_.GetBoard().GetSize(); ++x) {
            b.emplace_back();
            for (unsigned y = 0; y < board_.GetBoard().GetSize(); ++y) {
                QGraphicsPixmapItem* item = new QGraphicsPixmapItem(blank);
                b[x].push_back(item);
                item->setScale(pieceSize / item->boundingRect().width());
                //item->setPos((board_.GetBoard().GetSize() - 1 - x) * pieceSize, (board_.GetBoard().GetSize() - 1 - y) * pieceSize);
                item->setPos(y * pieceSize, x * pieceSize);
                addItem(item);
            }
        }
        repaint();
    }


    void BoardGraphics::repaint() {
        for (unsigned x = 0; x < board_.GetBoard().GetSize(); ++x) {
            for (unsigned y = 0; y < board_.GetBoard().GetSize(); ++y) {
                auto& piece = b[x][y];
                Color color;
                bool occupied = board_.GetBoard().GetField(x, y).GetStatus(color);
                if (!occupied)
                    piece->setPixmap(blank);
                else if (color == Color::BLACK)
                    piece->setPixmap(blackDisc);
                else
                    piece->setPixmap(whiteDisc);
            }
        }

        QPixmap& pixmap = board_.GetCurrentPlayer().GetColor() == Color::BLACK ? blackDiscLowOpacity : whiteDiscLowOpacity;

        for(const auto& c: changes){
            b[c.GetX()][c.GetY()]->setPixmap(pixmap);
        }
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
        if (mx < 0 || mx >= width() || my < 0 || my >= height())
            return;

        unsigned x = static_cast<unsigned>(mx / getPieceSize());
        unsigned y = static_cast<unsigned>(my / getPieceSize());

        changes.clear();
        changes = board_.GetLogic().PrepareTurn(y, x, board_.GetCurrentPlayer().GetColor());

        repaint();
    }

    void BoardGraphics::enterSlot(){
        mouseOver = true;
    }

    void BoardGraphics::leaveSlot(){
        mouseOver = false;
    }

    double BoardGraphics::getPieceSize() const {
        return static_cast<double>(size) / board_.GetBoard().GetSize();
    }
}
