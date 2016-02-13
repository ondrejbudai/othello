//
// Created by ondra on 12.2.16.
//

#include <QApplication>

#include "OthelloGui.hh"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    othello::OthelloGui o;
    o.show();

    return app.exec();
}
