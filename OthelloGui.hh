//
// Created by ondra on 13.2.16.
//

#ifndef OTHELLO_OTHELLOGUI_HH
#define OTHELLO_OTHELLOGUI_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>

namespace othello {
    class OthelloGui : public QWidget {
    public:
        QGraphicsScene* scene;
        QGraphicsView* view;

        OthelloGui();
    };
}

#endif //OTHELLO_OTHELLOGUI_HH
