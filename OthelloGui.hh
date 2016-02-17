//
// Created by ondra on 13.2.16.
//

#ifndef OTHELLO_OTHELLOGUI_HH
#define OTHELLO_OTHELLOGUI_HH

#include <QGraphicsView>
#include "PlayerSelection.hh"
#include "MainGame.hh"

namespace Ui{
    class OthelloGui;
}

namespace othello {
    class OthelloGui : public QWidget {

        Q_OBJECT

    public slots:
        void on_ButtonNewGame_clicked();
        void ShowGameBoard();
        void WriteScore(int white, int black);
        void EndOfGame();
    
    private:
        Ui::OthelloGui *ui;
        std::unique_ptr<MainGame> game_;
        QGraphicsScene *startScene;
        QGraphicsView  *startView;
        PlayerSelection* playerScreen;
        QGraphicsScene* scene;
        QGraphicsView* view;

    public:
        explicit OthelloGui(QWidget *parent = 0);
    };
}

#endif //OTHELLO_OTHELLOGUI_HH
