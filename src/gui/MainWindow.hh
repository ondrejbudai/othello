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

    /**
     * Hlavní okno, obsahuje panely s jednotlivými instancemi her
     */
    class MainWindow : public QTabWidget {
    Q_OBJECT
    private:
        /**
         * @brief Definice grafiky widgetu
         */
        Ui::MainWindow ui_;

        /**
         * @brief Počet vytvořených her od začátku
         */
        unsigned games_ = 0;

        /**
         * @brief Přidat další záložku se hrou
         */
        void AddGame();

    public:

        /**
         * Konstruktor widgetu
         * @param  parent Rodičovský widget
         */
        explicit MainWindow(QWidget* parent = nullptr);

    private slots:

        /**
         * Slot na změnu záložky
         * @param index Index záložky, na kterou se uživatel přepnul
         */
        void TabChangedSlot(int index);

        /**
         * Slot na zavření záložky
         * @param index Index zavírané záložky
         */
        void CloseRequestSlot(int index);

    };
}


#endif //OTHELLO_MAINWINDOW_HH
