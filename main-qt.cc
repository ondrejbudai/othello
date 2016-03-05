#include <QApplication>

#include "MainWindow.hh"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    othello::MainWindow o;
    o.show();

    return app.exec();
}
