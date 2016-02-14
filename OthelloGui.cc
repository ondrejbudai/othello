#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QGraphicsSceneMouseEvent>
#include <QScrollBar>
#include <QGraphicsRectItem>
#include <iostream>
#include <QResizeEvent>
#include "OthelloGui.hh"
#include "MainGame.hh"
#include "ui_OthelloGui.h"

namespace othello {
    constexpr unsigned GAME_SIZE = 200;

    class GraphicsScene : public QGraphicsScene {
    public:
        MainGame game_;
        std::vector<std::vector<QGraphicsRectItem*>> b;
        unsigned size;

        GraphicsScene() : QGraphicsScene{0, 0, GAME_SIZE, GAME_SIZE}, game_(10, PlayerType::HUMAN, PlayerType::AI),
                          size{GAME_SIZE} {
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

        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) {
            game_.event(mouseEvent->scenePos().x() / getPieceSize(), mouseEvent->scenePos().y() / getPieceSize());
            repaint();
            QGraphicsScene::mouseReleaseEvent(mouseEvent);
        }

        double getPieceSize() const {
            const GameBoard& board = game_.getLogic().getBoard();
            return double(double(size) / board.getSize());
        }

        void setSize(QSize s) {
            size = s.width() > s.height() ? s.height() : s.width();
            repaint();
        }
    };

    class GraphicsView : public QGraphicsView {
    public:
        GraphicsView(QGraphicsScene* s) : QGraphicsView(s) { }

        virtual void resizeEvent(QResizeEvent* event) {
            fitInView(0, 0, GAME_SIZE, GAME_SIZE, Qt::KeepAspectRatio);
            //dynamic_cast<GraphicsScene*>(scene())->setSize(event->size());
        }
    };

    void OthelloGui::ShowGameBoard(){
        ui->gameBoard->layout()->addWidget(view);
    }

    void OthelloGui::on_ButtonPlayGame_clicked(){
        ShowGameBoard();
    }

    OthelloGui::OthelloGui(QWidget *parent): QWidget(parent), ui(new Ui::OthelloGui) {
        ui->setupUi(this);      
        scene = new GraphicsScene;
        view = new GraphicsView(scene);
    }
}

