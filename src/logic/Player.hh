/**
* @file
* @brief Definice abstraktního hráče.
* @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
* @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
*/

#ifndef OTHELLO_PLAYER_HH
#define OTHELLO_PLAYER_HH

#include<string>
#include "GameLogic.hh"

namespace othello {

    /**
     * Hráč hry.
     * @class Player
     */
    class Player {
    protected:

        /**
         * Farba hráča.
         * @var color_
         */
        Color color_;

        /**
         * Meno hráča.
         * @var name_
         */
        std::string name_;

        /**
         * Referenica na hernú logiku.
         * @var logic_
         */
        const GameLogic& logic_;
    public:

        /**
         * Konšturktor hráča.
         * @method Player
         * @arg   c   Farba hráča.
         * @arg logic Referenica na GameLogic
         */
        Player(Color c, const GameLogic& logic) : color_{c}, logic_{logic} { }

        /**
         * Deštruktor hráča.
         * @method ~Player
         */
        virtual ~Player(){}

        /**
         * Výpočet pozície, ktorú chce hráč hrať.
         * @method Play
         * @return Súradnice, ktoré chce hráč zahrať.
         */
        virtual Coords Play() { return {0, 0}; }

        /**
         * Vráti farbu hráča.
         * @method GetColor
         * @return Farba hráča.
         */
        virtual Color GetColor() const { return color_; }

        /**
         * Overenie či sa jedná o človeka, alebo počítač.
         * @method IsAi
         * @return False
         */
        virtual bool IsAi() const { return false; }

        /**
         * Nastaví meno hráča.
         * @method SetName
         * @param  name    Meno, ktoré má byť hráčovy nastavené.
         */
        void SetName(std::string name) { name_ = name; }

        /**
         * Vráti meno hráča.
         * @method GetName
         * @return Meno hráča.
         */
        std::string GetName() {return name_;}
    };
}

#endif //OTHELLO_PLAYER_HH
