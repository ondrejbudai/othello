//
// Created by ondra on 13.2.16.
//

#ifndef OTHELLO_OTHELLOGUI_HH
#define OTHELLO_OTHELLOGUI_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>

namespace Ui{
    class OthelloGui;
}

namespace othello {
    class OthelloGui : public QWidget {

        Q_OBJECT

    public slots:
        void on_ButtonNewGame_clicked();
            
    private:
        Ui::OthelloGui *ui;
        QGraphicsScene *startScene;
        QGraphicsView  *startView;
        QGraphicsScene *startSceneLight;
        QGraphicsView  *startViewLight;
        QWidget *playerScreen;
    public:
        QGraphicsScene* scene;
        QGraphicsView* view;
        void ShowGameBoard();
        

        explicit OthelloGui(QWidget *parent = 0);
    };
}

#endif //OTHELLO_OTHELLOGUI_HH
