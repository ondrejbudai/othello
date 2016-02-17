#include "GraphicsScene.hh"

namespace othello {
    constexpr unsigned AI_DELAY = 1000;
    constexpr unsigned F1_DELAY = 10000;//len nahardkodene, treba prerobit
    constexpr unsigned F2_DELAY = 10000;//detto

    GraphicsScene::GraphicsScene(MainGame &gm) : QGraphicsScene{0, 0, GAME_SIZE, GAME_SIZE},
                                                 game_{gm}, size{GAME_SIZE} {

        //za kolko zamrzne
        freezeTimer = new QTimer(this);
        freezeTimer->setSingleShot(true);

        //za kolko odmrzne
        unfreezeTimer = new QTimer(this);
        unfreezeTimer->setSingleShot(true);
        
        //za kolko odohra AI
        timer = new QTimer(this);
        timer->setSingleShot(true);
        
        //nainicalizujeme si grafiku
        blackDisc = new QImage("img/blackDisc.jpg");
        whiteDisc = new QImage("img/whiteDisc.jpg");
        blank = new QImage("img/blank.jpg");
        blackDiscFrozen = new QImage("img/blackDiscFrozen.jpg");
        whiteDiscFrozen = new QImage("img/whiteDiscFrozen.jpg");

        const GameBoard& board = game_.getLogic().getBoard();
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
        connect(freezeTimer,SIGNAL(timeout()), this, SLOT(WaitingOnFreezingEnded()));
        connect(unfreezeTimer,SIGNAL(timeout()), this, SLOT(TimeToUnfreeze()));
        freezeTimer->start(F1_DELAY);//zacneme pocitat do prveho zamrznutia
        if (game_.getCurrentPlayer().isAi()) {
            timer->start(AI_DELAY);
        }
    }


    void  GraphicsScene::repaint() {
        //const GameBoard& board = game_.getLogic().getBoard();
        GameBoard& board = game_.getLogic().getBoard();
        
        if (!game_.IsRunning()) {
            disconnect(timer,SIGNAL(timeout()), this, SLOT(TickingClocks()));
            return;
        }
        //ak mozme odrazit, tak odmrazime skor, ako vykreslime scenu
        if (canUnfreez == true){
            //unfreez all
            board.UnfreezeAll();
            canUnfreez = false;
            //zapnem casovac na mrznutie
            freezeTimer->start(F1_DELAY);//zacneme pocitat do prveho zamrznutia
        }
        

        const double pieceSize = getPieceSize();
        for (unsigned x = 0; x < board.getSize(); ++x) {
            for (unsigned y = 0; y < board.getSize(); ++y) {
                QGraphicsPixmapItem* newItem;
                removeItem(b[x][y]);
                delete b[x][y];
                if (!board.isOccupied(x, y)) {
                    newItem = new QGraphicsPixmapItem(QPixmap::fromImage(*blank));
                } else if (board.isFrozen(Coords{x,y})){
                    if (board.GetColor(x,y) == Color::BLACK)
                        newItem = new QGraphicsPixmapItem(QPixmap::fromImage(*blackDiscFrozen));
                    else 
                        newItem = new QGraphicsPixmapItem(QPixmap::fromImage(*whiteDiscFrozen));
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

        emit(Score_Changed(black, white));
        if (game_.isEnd())
            emit (EndOfGame());
    }

    void  GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) {
        if (!game_.getCurrentPlayer().isAi() && game_.IsRunning()) {
            const GameBoard& board = game_.getLogic().getBoard();
            int nX = mouseEvent->scenePos().x() / getPieceSize();
            int nY =  mouseEvent->scenePos().y() / getPieceSize();
            if (nX < 0 || nY < 0 || unsigned(nX) >= board.getSize() || unsigned(nY) >= board.getSize())
                return;
            if (!game_.event(nX, nY))
                return;    
            if (game_.getCurrentPlayer().isAi()) {
                this->timer->start(AI_DELAY);
            }
            repaint();
        }
    }

    double  GraphicsScene::getPieceSize() const {
        const GameBoard& board = game_.getLogic().getBoard();
        return double(double(size) / board.getSize());
    }


    void GraphicsScene::TickingClocks(){
        Player p = game_.getCurrentPlayer();
        Coords c = p.play();
        if (game_.IsRunning())
            if (!game_.event(c.GetX(), c.GetY()))
                return;
        repaint();
        if (game_.getCurrentPlayer().isAi()) {
            this->timer->start(AI_DELAY);
        }
    }

    //cas vyprsal, zamrzneme
    void GraphicsScene::WaitingOnFreezingEnded(){
        GameBoard& board = game_.getLogic().getBoard();
        //zamrzneme random kamene
        board.SetRandomToFreeze(1);
        //spustime dalsi casovac
        unfreezeTimer->start(F2_DELAY);//zacneme pocitat do prveho zamrznutia
    }

    //kamene by mali odmrznut
    void GraphicsScene::TimeToUnfreeze(){
        if (!canUnfreez){//mozno stale cakame na odmrznutie
            //nastavim len flag ze mozu odrznut a na konci tahu sa musi flag skontrolovat
            canUnfreez = true;
        }
    }

}


