/**
 * @file
 * @brief Widget obsahující jednu instanci hry.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_OTHELLOGUI_HH
#define OTHELLO_OTHELLOGUI_HH

#include <QTimer>
#include <QGraphicsView>
#include "PlayerSelection.hh"
#include "../logic/MainGame.hh"
#include "InfoPanel.hh"
#include "BoardGraphics.hh"
#include "StartPanel.hh"
#include "ui_OthelloGui.h"
#include "../logic/CommandManager.hh"

namespace othello {

    /**
     * @brief Třída obsahující jednu instanci hry - všechny panely, které k ní patří a hru samotnou
     */
    class OthelloGui : public QWidget {
    Q_OBJECT

    private:
        /**
         * @brief Definice grafiky widgetu
         */
        Ui::OthelloGui ui_;

        /**
         * @brief Instance hry
         */
        std::unique_ptr<MainGame> game_;

        /**
         * @brief Manažer příkazů pro operace undo a redo
         */
        CommandManager cmd_;

        /**
         * @brief Startovní scéna - zobrazuje se pod výběrem hráčů
         */
        QGraphicsScene* start_scene_;

        /**
         * @brief Startovní pohled - zobrazuje se pod výběrem hráčů
         */
        QGraphicsView* start_view_;

        /**
         * @brief Widget na výběr hráčů před zahájením hry
         */
        PlayerSelection* player_screen_;

        /**
         * @brief Herní deska
         */
        BoardGraphics* scene_;

        /**
         * @brief Pohled na herní desku
         */
        GraphicsView* view_;

        /**
         * @brief Informační panek, který zobrazuje informace o aktuální hře
         */
        InfoPanel* info_panel_;

        /**
         * @brief Časovač pro AI
         */
        QTimer* timer_;

        /**
         * @brief Úvodní panel s informacemi jako nová hra a načíst hru
         */
        StartPanel* start_panel_;

        /**
         * @brief Může hrát AI (není hra v stavu pauza)
         */
        bool play_ai_ = true;

        /**
         * @brief Vytvoř a zobraz herní desku
         * @param p1        Typ prvního hráče
         * @param p2        Typ druhého hráče
         * @param boardSize Velikost desky
         * @param names     Jména hráčů
         */
        void ShowGameBoard(PlayerType p1, PlayerType p2, unsigned boardSize,
                           const std::pair<std::string, std::string>& names);

        /**
         * @brief Překresli hru
         */
        void RepaintGame();

        /**
         * @brief Ukonči hru
         */
        void EndGame();

    public:
        /**
         * @brief Konstruktor instance hry
         * @param  parent Rodičovský widget
         */
        explicit OthelloGui(QWidget* parent = nullptr);

    signals:
        /**
         * @brief Signál na změnu ikony u tlačítka ovládající pauzu.
         */
        void ChangeIcon();

    public slots:

        /**
         * @brief Slot na nahrávání konfigurace hry
         */
        void LoadGameConfiguration();

        /**
         * @brief Tlačítko nové hry
         */
        void ButtonNewGame();

        /**
         * @brief Tlačítko uložit hru
         */
        void ButtonSaveGame();

        /**
         * @brief Tlačítko načíst hru
         */
        void ButtonLoadGame();

        /**
         * @brief Tlačítko pauzy/znovuspuštění
         */
        void PlayPause();

        /**
         * @brief Tlačítko akce redo
         */
        void ButtonREDO();

        /**
         * @brief Tlačítko akce undo
         */
        void ButtonUNDO();

        /**
         * @brief Zobraz informační panel
         */
        void ShowInfoPanel();

        /**
         * Slot na příjem signálu, pokud herní deska přijala kliknutí myši
         * @param mx Souřadnice X
         * @param my Souřadnice Y
         */
        void GameClickSlot(unsigned mx, unsigned my);

        /**
         * @brief Slot vypršení času časovače pro AI
         */
        void TimeoutSlot();
    };
}

#endif //OTHELLO_OTHELLOGUI_HH
