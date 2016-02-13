//
// Do NOT try this at home
// YOU HAVE BEEN WARNED...
//   _____
//  /     \
// | () () |
//  \  ^  /
//   ||||
//   ||||
//

#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QGraphicsSceneMouseEvent>
#include <QScrollBar>
#include <QGraphicsRectItem>
#include <iostream>
#include "OthelloGui.hh"
#include "MainGame.hh"

namespace othello {
    constexpr unsigned GAME_SIZE = 200;

    class GraphicsScene : public QGraphicsScene {
    public:
        MainGame game_;
        std::vector<std::vector<QGraphicsRectItem*>> b;

        GraphicsScene() : QGraphicsScene{0, 0, GAME_SIZE, GAME_SIZE}, game_(10, PlayerType::HUMAN, PlayerType::AI) {
            addRect(0, 0, GAME_SIZE, GAME_SIZE);
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
        }

        void repaint() {
            const GameBoard& board = game_.getLogic().getBoard();
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
                }
            }
        }

        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) {
            game_.event(mouseEvent->scenePos().x() / getPieceSize(), mouseEvent->scenePos().y() / getPieceSize());
            repaint();
            QGraphicsScene::mouseReleaseEvent(mouseEvent);
        }

        unsigned getPieceSize() const {
            const GameBoard& board = game_.getLogic().getBoard();
            return unsigned(double(GAME_SIZE) / board.getSize());
        }
    };

    class GraphicsView : public QGraphicsView {
    public:
        GraphicsView(QGraphicsScene* s) : QGraphicsView(s) { }

        virtual void resizeEvent(QResizeEvent* event) {
            fitInView(0, 0, GAME_SIZE, GAME_SIZE, Qt::KeepAspectRatio);
        }
    };

    OthelloGui::OthelloGui() {
        scene = new GraphicsScene;
        view = new GraphicsView(scene);
//        view->setFixedSize(GAME_SIZE, GAME_SIZE);
        view->horizontalScrollBar()->hide();
        view->verticalScrollBar()->hide();

        QGridLayout* layout = new QGridLayout;
        layout->addWidget(view);
        setLayout(layout);
    }
}

