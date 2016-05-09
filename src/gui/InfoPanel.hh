/**
 * @file
 * @brief Widget ukazující informace o aktuálně hrané hře.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_INFOPANEL_HH
#define OTHELLO_INFOPANEL_HH

#include <QWidget>
#include <QFrame>
#include <string>
#include "ui_InfoPanel.h"
#include "../logic/Field.hh"

namespace othello {
    /**
     * @brief Panel zobrazující informace o aktuální hře
     */
    class InfoPanel : public QFrame {
    Q_OBJECT

    private:
        /**
         * @brief Definice grafiky widgetu
         */
        Ui::InfoPanel ui_;

    public:
        /**
         * @brief Konstruktor panelu
         * @param parent Rodičovský widget
         */
        explicit InfoPanel(QWidget* parent = nullptr);

        /**
         * @brief Aktualizuj skóre
         * @param score Skóre obou hráčů
         */
        void WriteScore(std::pair<unsigned, unsigned> score);

        /**
         * @brief Nastav jména hráčů
         * @param names Jméno obou hráčů
         */
        void SetNames(const std::pair<std::string, std::string>& names);

        /**
         * @brief Zvýrazni jméno aktuálně hrajícího hráče
         * @param c Aktuálně hrající hráč
         */
        void HighlightPlayer(Color c);

        /**
         * @brief Změn ikonu zobrazující stav hry (při procházení historií)
         * @param to Nový stav ikony
         */
        void ChangeIcon(bool to);

    signals:

        /**
         * @brief Signál kliknutí z tlačítka ulož hru
         */
        void on_ButtonSaveGame_clicked();

        /**
         * @brief Signál kliknutí z tlačítka zpět
         */
        void on_ButtonUNDO_clicked();

        /**
         * @brief Signál kliknutí z tlačítka vpřed
         */
        void on_ButtonREDO_clicked();

        /**
         * @brief Signál kliknutí z tlačítka pokračuj/pauza
         */
        void on_PlayPause_clicked();

        /**
         * @brief Signál zmeny zaškrtávatka pre zobrazovanie pomoci
         */
        void on_CheckHelp_stateChanged(int state);


    };
}

#endif //OTHELLO_INFOPANEL_HH
