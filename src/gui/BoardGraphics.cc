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
    }

    void GraphicsView::mouseMoveEvent(QMouseEvent* mouse_event) {
        emit MouseMoveSignal(mapToScene(mouse_event->pos()));
    }

    void GraphicsView::enterEvent(QEvent*){
        emit EnterSignal();
    }

    void GraphicsView::leaveEvent(QEvent*){
        emit LeaveSignal();
    }

    BoardGraphics::BoardGraphics(const MainGame& game)
        : QGraphicsScene{0, 0, GAME_SIZE, GAME_SIZE}, size_{GAME_SIZE}, game_{game} {

        // nahrati spritu pro vsechny obrazky
        black_disc_ = QPixmap::fromImage(QImage("img/blackDisc.jpg"));
        black_disc_shadow_ = QPixmap::fromImage(QImage("img/blackLowOpacity.png"));
        white_disc_ = QPixmap::fromImage(QImage("img/whiteDisc.jpg"));
        white_disc_shadow_ = QPixmap::fromImage(QImage("img/whiteLowOpacity.png"));
        blank_ = QPixmap::fromImage(QImage("img/blank.jpg"));

        // vytvoreni metice spritu pro obrazky
        const double pieceSize = GetPieceSize();
        for (unsigned x = 0; x < game_.GetBoard().GetSize(); ++x) {
            graphics_matrix_.emplace_back();
            for (unsigned y = 0; y < game_.GetBoard().GetSize(); ++y) {
                QGraphicsPixmapItem* item = new QGraphicsPixmapItem(blank_);
                graphics_matrix_[x].push_back(item);
                item->setScale(pieceSize / item->boundingRect().width());
                item->setPos(y * pieceSize, x * pieceSize);
                addItem(item);
            }
        }

        // prekresleni aktualniho stavu
        Repaint();
    }


    void BoardGraphics::Repaint() {

        // prekresli vsechny pole
        for (unsigned x = 0; x < game_.GetBoard().GetSize(); ++x) {
            for (unsigned y = 0; y < game_.GetBoard().GetSize(); ++y) {
                auto& piece = graphics_matrix_[x][y];
                Color color;
                bool occupied = game_.GetBoard().GetField(x, y).GetStatus(color);
                if (!occupied)
                    piece->setPixmap(blank_);
                else if (color == Color::BLACK)
                    piece->setPixmap(black_disc_);
                else
                    piece->setPixmap(white_disc_);
            }
        }

        // pokud je mys nad hraci deskou, prekresli vsechna pole, kde by doslo po kliknuti ke zmene
        if(mouse_over_){
            QPixmap& pixmap = game_.GetCurrentPlayer().GetColor() == Color::BLACK ? black_disc_shadow_ : white_disc_shadow_;

            for(const auto& c: current_changes_){
                graphics_matrix_[c.GetX()][c.GetY()]->setPixmap(pixmap);
            }
        }
    }

    void BoardGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) {
        double mx = mouseEvent->scenePos().x();
        double my = mouseEvent->scenePos().y();

        // zjisti, zda jsme stale uvnitr widgetu
        if (mx < 0 || mx > width() || my < 0 || my > height())
            return;

        // transformuj souradnice
        unsigned x = static_cast<unsigned>(mx / GetPieceSize());
        unsigned y = static_cast<unsigned>(my / GetPieceSize());

        emit ClickSignal(y, x);
    }

    void BoardGraphics::MouseMoveSlot(QPointF coords) {
        double mx = coords.x();
        double my = coords.y();

        if (mx < 0 || mx >= width() || my < 0 || my >= height())
            return;

        unsigned x = static_cast<unsigned>(mx / GetPieceSize());
        unsigned y = static_cast<unsigned>(my / GetPieceSize());

        // pridej vsechny mozne změněné pole, pokud by uzivatel klikl na pole, kde je aktuálně kurzor
        current_changes_.clear();
        current_changes_ = game_.GetLogic().PrepareTurn(y, x, game_.GetCurrentPlayer().GetColor());

        Repaint();
    }

    void BoardGraphics::EnterSlot(){
        mouse_over_ = true;
    }

    void BoardGraphics::LeaveSlot(){
        mouse_over_ = false;
    }

    double BoardGraphics::GetPieceSize() const {
        return static_cast<double>(size_) / game_.GetBoard().GetSize();
    }
}
