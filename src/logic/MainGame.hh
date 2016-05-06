/**
* @file
* @brief Správa hry.
* @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
* @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
*/

#ifndef OTHELLO_MAINGAME_HH
#define OTHELLO_MAINGAME_HH

#include <memory>
#include "AI.hh"
#include "GameBoard.hh"
#include <fstream>

namespace othello {
    /**
     * Typy hráčov.
     * @enum PlayerType
     */
    enum class PlayerType {
        HUMAN, AI
    };

    /**
     * Správa hry.
     * @class MainGame
     */
    class MainGame {
    private:
        /**
         * Referencia na GameLogic
         * @var logic_
         */
        GameLogic logic_;

        /**
         * Uloženie hráčov.
         * @var players_
         */
        std::vector<std::unique_ptr<Player>> players_;

        /**
         * Aktuálny hráč na ťahu
         * @var current_player_num
         */
        int current_player_num_ = 0;
    public:

        /**
         * Konštruktor pre správu hry.
         * @method MainGame
         * @arg size  Veľkosť hracej plochy.
         * @arg white Type bieleho hráča.
         * @arg black Type čierneho hráča.
         */
        MainGame(unsigned size, PlayerType white, PlayerType black);

        /**
         * Herná udalosť = položenie kameňa.
         * @method Event
         * @param  x     X-ová súradnica.
         * @param  y     Y-ová súradnica.
         * @return       True ak správny pohyb, inak False.
         */
        bool Event(unsigned x, unsigned y); // event funkce

        /**
         * Vráti aktuálneho hráča.
         * @method GetCurrentPlayer
         * @return Aktuálny hráč.
         */
        const Player& GetCurrentPlayer() const { return *players_[current_player_num_]; }

        /**
         * Vracia stav hry.
         * @method IsEnd
         * @return True ak už nie sú validné ťahy, inak false.
         */
        bool IsEnd() const;

        /**
         * Vracia stav hry pre hráča.
         * @method CanPlay
         * @param  color   Hráč, pre ktorého zistujeme stav hry.
         * @return         True ak má validný ťah, inak false.
         */
        bool CanPlay(Color color) const;

        /**
         * Vracia referenciu na hernú logiku.
         * @method GetLogic
         * @return Konštantná referencia na hernú logiku.
         */
        const GameLogic& GetLogic() const { return logic_; }

        /**
         * Vracia referenciu na hernú logiku.
         * @method GetLogic
         * @return Referencia na hernú logiku.
         */
        GameLogic& GetLogic() { return logic_; }

        /**
         * Vracia hraciu dosku.
         * @method GetBoard
         * @return Konštatná referencia na GameBoard.
         */
        const GameBoard& GetBoard() const {return logic_.GetBoard();}

        /**
         * Nastaví mená hráčov.
         * @method SetNames
         * @param  names    Mená hráčov, prvý čierny.
         */
        void SetNames(const std::pair<std::string, std::string>& names);

        /**
         * Vráti mená hráčov.
         * @method GetNames
         * @return Mená hráčov, prvý čierny.
         */
        std::pair<std::string, std::string> GetNames();

        /**
         * Uloží aktuány stav hry do súbora.
         * @method SaveGameToFile
         * @param  thisFile       pripravený popisovač súboru.
         * @return                True ak všetko OK, inak false.
         */
        bool SaveGameToFile(std::ofstream &thisFile);

        /**
         * Nastaví aktuálneho hráča.
         * @method SetCurrentPlayer
         * @param  n                Nové číslo aktuálneho hráča.
         */
        void SetCurrentPlayer(int n) {current_player_num_ = n;}

        /**
         * Vráti číslo aktuálneho hráča.
         * @method GetCurrentPlayerNum
         * @return Číslo aktuálneho hráča.
         */
        int GetCurrentPlayerNum(){ return current_player_num_;}

        /**
         * Zavolá AI, aby zahra ťah.
         * @method TellAIToPlay
         * @return Súradnice ťahu, ktoré si AI vybral.
         */
        Coords TellAIToPlay();

    };
}


#endif //OTHELLO_MAINGAME_HH
