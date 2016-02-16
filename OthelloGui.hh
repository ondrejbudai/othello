//
// Created by ondra on 13.2.16.
//

#ifndef OTHELLO_OTHELLOGUI_HH
#define OTHELLO_OTHELLOGUI_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include "MainGame.hh"

namespace Ui{
    class OthelloGui;
}

namespace othello {
    class OthelloGui : public QWidget {

        Q_OBJECT
    signals:
        void on_ButtonStartGame_clicked();

    public slots:
        void on_ButtonNewGame_clicked();
        void ShowGameBoard();
        void WriteScore(int white, int black);
        void EndOfGame();
            
    private:
        Ui::OthelloGui *ui;
        MainGame game_;
        QGraphicsScene *startScene;
        QGraphicsView  *startView;
        QGraphicsScene *startSceneLight;
        QGraphicsView  *startViewLight;
        QWidget *playerScreen;
        QWidget *topFeature;
        QGraphicsPixmapItem *startImageLight;
        QGraphicsScene* scene;
        QGraphicsView* view;

    public:
        

        explicit OthelloGui(QWidget *parent = 0);
    };
}

#endif //OTHELLO_OTHELLOGUI_HH
