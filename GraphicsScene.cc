#include "GraphicsScene.hh"

namespace othello {
    constexpr unsigned AI_DELAY = 0;

    GraphicsScene::GraphicsScene(MainGame &gm) : QGraphicsScene{0, 0, GAME_SIZE, GAME_SIZE},
                                     game_{&gm}, size{GAME_SIZE} {

        
        timer = new QTimer(this);
        timer->setSingleShot(true);
        blackDisc = new QImage("img/blackDisc.jpg");
        whiteDisc = new QImage("img/whiteDisc.jpg");
        blank = new QImage("img/blank.jpg");

        const GameBoard& board = game_->getLogic().getBoard();
        const double pieceSize = getPieceSize();
        for (unsigned x = 0; x < board.getSize(); ++x) {
            b.emplace_back();
            for (unsigned y = 0; y < board.getSize(); ++y) {
                QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*blank));
                b[x].push_back(item);
                item->setScale(pieceSize / item->boundingRect().width());
                item->setPos(x * pieceSize, y * pieceSize);
                addItem(item);
            }
        }
        repaint();
        connect(timer,SIGNAL(timeout()), this, SLOT(TickingClocks()));
        if (game_->getCurrentPlayer().isAi()) {
            timer->start(AI_DELAY);
        }
    }


    void  GraphicsScene::repaint() {
        if (!game_->IsRunning()){
            disconnect(timer,SIGNAL(timeout()), this, SLOT(TickingClocks()));
            return;
        }

        const GameBoard& board = game_->getLogic().getBoard();
        const double pieceSize = getPieceSize();
        for (unsigned x = 0; x < board.getSize(); ++x) {
            for (unsigned y = 0; y < board.getSize(); ++y) {
                QGraphicsPixmapItem* newItem;
                removeItem(b[x][y]);
                delete b[x][y];
                if (!board.isOccupied(x, y)) {
                    newItem = new QGraphicsPixmapItem(QPixmap::fromImage(*blank));
                } else if (board.GetColor(x, y) == Color::BLACK) {
                    newItem = new QGraphicsPixmapItem(QPixmap::fromImage(*blackDisc));
                } else {
                    newItem = new QGraphicsPixmapItem(QPixmap::fromImage(*whiteDisc));
                }
                newItem->setScale(pieceSize / newItem->boundingRect().width());
                newItem->setPos(x * pieceSize, y * pieceSize);
                addItem(newItem);
                b[x][y] = newItem;


            }
        }
        //Zistime nove skore

        int white = 0;
        int black = 0;
        board.CountScore(black, white);
        std::cout<<"Biely: "<<white<<"   Cierny: "<<black<<std::endl;
        emit(Score_Changed(black, white));
        if (!game_->canPlay(game_->getCurrentPlayer().getColor()))     
            emit (EndOfGame());
    }

    void  GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) {
        if (!game_->getCurrentPlayer().isAi() && game_->IsRunning()) {
            game_->event(mouseEvent->scenePos().x() / getPieceSize(), mouseEvent->scenePos().y() / getPieceSize());
            if (game_->getCurrentPlayer().isAi()) {
                this->timer->start(AI_DELAY);
            }
            repaint();
        }
        //QGraphicsScene::mouseReleaseEvent(mouseEvent);
    }

    double  GraphicsScene::getPieceSize() const {
        const GameBoard& board = game_->getLogic().getBoard();
        return double(double(size) / board.getSize());
    }

    /*void  GraphicsScene::setSize(QSize s) {
        size = s.width() > s.height() ? s.height() : s.width();
        repaint();
    }
    */


    void GraphicsScene::TickingClocks(){
        Player p = game_->getCurrentPlayer();
        Coords c = p.play();
        if (game_->IsRunning())
            game_->event(c.GetX(), c.GetY());
        repaint();
        if (game_->getCurrentPlayer().isAi()) {
            this->timer->start(AI_DELAY);
        }
    }
}


