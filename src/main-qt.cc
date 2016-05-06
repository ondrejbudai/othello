/**
* @file
* @brief Spouštěcí soubor pro grafickou verzi.
* @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
* @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
*/

#include <QApplication>

#include "gui/MainWindow.hh"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    othello::MainWindow o;
    o.show();

    return app.exec();
}
