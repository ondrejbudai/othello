/**
 * @file
 * @brief Hlavní okno aplikace.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#include "MainWindow.hh"
#include "OthelloGui.hh"

namespace othello {
    MainWindow::MainWindow(QWidget* parent) : QTabWidget{parent} {
        ui.setupUi(this);

        addGame();
        connect(this, &MainWindow::tabBarClicked, this, &MainWindow::tabChangedSlot);
        connect(this, &MainWindow::tabCloseRequested, this, &MainWindow::closeRequestSlot);
    }

    void MainWindow::tabChangedSlot(int index) {
        // pokud menime na jiny nez posledni, event nas nezajima
        if (index != count() - 1)
            return;

        // pridame hru
        addGame();
    }

    void MainWindow::closeRequestSlot(int index) {
        // pridavaci tab se nesmi zavrit
        if (index == count() - 1)
            return;

        // odstran tab
        removeTab(index);

        // pokud zbyl pouze pridavaci tab, pridame novy
        if (count() == 1)
            addGame();

        // pokud se pridavaci tab stane aktivnim, nastavime aktivnim tab predesly
        if (index == count() - 1)
            setCurrentIndex(index - 1);
    }

    void MainWindow::addGame() {
        int tabs = count();

        // smaz pridavaci tab, pokud existuje
        if (tabs > 0)
            removeTab(tabs - 1);

        // nastavime jmeno hry
        QString gameName("Game #");
        gameName.append(QString::number(++games));

        // pridame tab se hrou
        addTab(new OthelloGui, gameName);

        // pridame pridavaci tab
        addTab(new QWidget, "+");

        // smazeme zaviraci tlacitko pridavacimu tabu
        tabBar()->setTabButton(count() - 1, QTabBar::RightSide, NULL);
    }
}
