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
#include <map>

namespace othello {

    /**
     * @brief Herná logika pre validáciu ťahov.
     * @class GameLogic
     */
    class GameLogic {
    private:

        /**
         * @brief Uloženie aktuálnej GameBoard.
         * @var board_
         */
        GameBoard board_;

    public:

        /**
         * @brief Konštruktor hernej logicky.
         * @method GameLogic
         * @arg size  Veľkosť hracej dosky.
         */
        GameLogic(unsigned size) : board_{size} { }

        /**
         * @brief Kontrola validity ťahu a zistenie kameňov, ktoré sa majú obráťiť.
         * @method PrepareTurn
         * @param x   X súradnica pripravovaného ťahu.
         * @param y   Y súradnica pripravovaného ťahu.
         * @param addingColor   Farba hráča, ktorý hrá.
         * @return Všetky kamene, ktoré sa nastavia na farbu hráča.
         *
         */
        std::vector<Coords> PrepareTurn(unsigned x, unsigned y, Color addingColor) const;

        /**
         * @brief Zápis ťahu - nastavenie kameňov.
         * @method CommitTurn
         * @param  pieces     Všetky kamene, ktoré majú byť nastavené.
         * @param  player     Farba hráča, na ktorú maju byť kamene nastavené.
         */
        void CommitTurn(const std::vector<Coords>& pieces, Color player);

        /**
         * @brief Vráti referenciu na aktuálnu dosku.
         * @method GetBoard
         * @return Referencia na aktuálnu dosku.
         */
        const GameBoard& GetBoard() const { return board_; }

        /**
         * @brief Vráti aktuáne skóre.
         * @method GetScore
         * @return Pár skóre čierneho, skóre bieleho
         */
        std::pair<unsigned, unsigned> GetScore() const;

        /**
         * @brief Nastaví aktuálnu hraciu plochu.
         * @method SetGameBoard
         * @param  old          Hracia plocha, ktorá sa má nastaviť.
         */
        void SetGameBoard(const GameBoard &old){ board_.SetBoard(old);}

        /**
         * @brief Získa validné ťahy pre hráča.
         * @method GetValidMoves
         * @param  current          Aktuálny hráč.
         * @return Mapa súradníc a počtom obráteních kameňov.
         */
        std::multimap<unsigned, Coords> GetValidMoves(Color current) const;

        /**
         * @brief Zapíše možné ťahy.
         * @method MarkPossibleMoves
         * @param  current           Aktuálny hráč.
         */
        void MarkPossibleMoves(Color current);

        /**
         * Zmaže všetky dočasné značky.
         * @method ClearFlags
         */
        void ClearFlags();

        /**
         * @brief Vracia stav hry pre hráča.
         * @method CanPlay
         * @param  color   Hráč, pre ktorého zistujeme stav hry.
         * @return         True ak má validný ťah, inak false.
         */
        bool CanPlay(Color color) const;
    };
}


#endif //OTHELLO_GAMELOGIC_HH
