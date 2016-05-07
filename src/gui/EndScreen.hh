/**
 * @file
 * @brief Widget ukazující informace na konci hry.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_ENDSCREEN_HH
#define OTHELLO_ENDSCREEN_HH

#include <QFrame>
#include "ui_EndScreen.h"

namespace othello {

    /**
     * @brief Widget zobrazující výsledek hry.
     */
    class EndScreen : public QFrame {
    Q_OBJECT

    private:
        /**
         * @brief Definice grafiky widgetu
         */
        Ui::EndScreen ui_;

    public:

        /**
         * @brief Konstruktor obrazovky
         * @param parent Rodič prvku
         */
        explicit EndScreen(QWidget* parent = nullptr);

        /**
         * @brief Nastav jména hráčů
         * @param names Jména hráčů
         */
        void SetNames(const std::pair<std::string, std::string>& names);

        /**
         * @brief Nastav výsledná skóre
         * @param scores Skóre jednotlivých hráčů
         */
        void SetScores(const std::pair<unsigned, unsigned>& scores);
    };
}


#endif
