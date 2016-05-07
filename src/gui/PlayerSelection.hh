/**
 * @file
 * @brief Widget na vybírání hráčů.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef PLAYERSELECTION_H
#define PLAYERSELECTION_H

#include <QFrame>
#include "ui_PlayerSelection.h"

namespace othello {

    /**
     * @brief Widget umožňující nastavení hráčů v nové hře
     */
    class PlayerSelection : public QFrame
    {
        Q_OBJECT

    private:
        /**
         * @brief Definice grafiky widgetu
         */
        Ui::PlayerSelection ui_;

    public:

        /**
         * @brief Konstruktor widgetu
         * @param  parent Rodičovský objekt
         */
        explicit PlayerSelection(QWidget *parent = nullptr);

        /**
         * @brief Zjisti jména hráčů
         * @return Jména obou hráčů
         */
        std::pair<QString, QString> GetNames();

        /**
         * @brief Zjisti typy hráčů
         * @return Typy obou hráčů
         */
        std::pair<QString, QString> GetTypes();

        /**
         * Zjisti velikost hrací desky, kterou si uživatel zvolil
         * @return Velikost hrací desky
         */
        QString GetBoardSize();

    signals:
        /**
         * Signál kliknutí na tlačítko start nové hry
         */
        void on_ButtonStartGame_clicked();
    };

}

#endif // PLAYERSELECTION_H
