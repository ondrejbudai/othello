/**
 * @file
 * @brief Hlavní okno aplikace.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_MAINWINDOW_HH
#define OTHELLO_MAINWINDOW_HH

#include <QTabWidget>
#include "ui_MainWindow.h"


namespace othello {
    class MainWindow : public QTabWidget {
    Q_OBJECT
    private:
        Ui::MainWindow ui;

        void addGame();

        unsigned games = 0;
    public:
        explicit MainWindow(QWidget* parent = 0);

    public slots:

        void tabChangedSlot(int index);

        void closeRequestSlot(int index);

    };
}


#endif //OTHELLO_MAINWINDOW_HH
