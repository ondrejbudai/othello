/**
 * @file
 * @brief Panel na zahájení nové hry.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_STARTPANEL_HH
#define OTHELLO_STARTPANEL_HH

#include <QWidget>
#include <QFrame>
#include "ui_StartPanel.h"

namespace othello {

    /**
     * @brief Panel zobrazující se po vytvoření nové instance hry umožňující zahájit novou hru.
     */
    class StartPanel : public QFrame {
    Q_OBJECT

    private:
        /**
         * @brief Definice grafiky panelu
         */
        Ui::StartPanel ui_;

    public:
        /**
         * @brief Konstruktor panelu
         * @param  parent Rodičovský widget
         */
        explicit StartPanel(QWidget* parent = nullptr);

    signals:
        /**
         * @brief Signál tlačítka nahrát hru
         */
        void on_ButtonLoadGame_clicked();

        /**
         * @brief Signál tlačítka nová hra
         */
        void on_ButtonNewGame_clicked();
    };
}


#endif
