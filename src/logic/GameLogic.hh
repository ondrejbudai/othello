/**
 * @file
 * @brief Herní logika.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_GAMELOGIC_HH
#define OTHELLO_GAMELOGIC_HH

#include "GameBoard.hh"
#include <string>

namespace othello {

    /**
     * Herná logika pre validáciu ťahov.
     * @class Gameogic
     */
    class GameLogic {
    private:

        /**
         * Uloženie aktuálnej GameBoard.
         * @var board_
         */
        GameBoard board_;

    public:

        /**
         * Konštruktor hernej logicky.
         * @method GameLogic
         * @arg size  Veľkosť hracej dosky.
         */
        GameLogic(unsigned size) : board_{size} { }

        /**
         * Kontrola validity ťahu a zistenie kameňov, ktoré sa majú obráťiť.
         * @method PrepareTurn
         * @arg x   X súradnica pripravovaného ťahu.
         * @arg y   Y súradnica pripravovaného ťahu.
         * @arg addingColor   Farba hráča, ktorý hrá.
         * @return Všetky kamene, ktoré sa nastavia na farbu hráča.
         *
         */
        std::vector<Coords> PrepareTurn(unsigned x, unsigned y, Color addingColor) const;

        /**
         * Zápis ťahu - nastavenie kameňov.
         * @method CommitTurn
         * @param  pieces     Všetky kamene, ktoré majú byť nastavené.
         * @param  player     Farba hráča, na ktorú maju byť kamene nastavené.
         */
        void CommitTurn(const std::vector<Coords>& pieces, Color player);

        /**
         * Vráti referenciu na aktuálnu dosku.
         * @method GetBoard
         * @return Referencia na aktuálnu dosku.
         */
        const GameBoard& GetBoard() const { return board_; }

        /**
         * Vráti aktuáne skóre.
         * @method GetScore
         * @return Pár skóre čierneho, skóre bieleho
         */
        std::pair<unsigned, unsigned> GetScore() const;

        /**
         * Nastaví aktuálnu hraciu plochu.
         * @method SetGameBoard
         * @param  old          Hracua plocha, ktorá sa má nastaviť.
         */
        void SetGameBoard(const GameBoard &old){ board_.SetBoard(old);}

    };
}


#endif //OTHELLO_GAMELOGIC_HH
