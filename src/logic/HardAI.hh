/**
 * @file
 * @brief Umělá inteligence pouze s predikcí na jeden tah dopředu.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_HARD_AI_HH
#define OTHELLO_HARD_AI_HH

#include <random>
#include "Player.hh"
#include "GameBoard.hh"

namespace othello {

    /**
     * @brief Varianta hráča ovládaného počítačom.
     */
    class HardAI : public Player {
    private:
        /**
         * @brief Mersanne-twister generátor.
         * @var random_
         */
        std::mt19937 random_;

        /**
         * @brief Level obtiažnosti.
         */
        double randomness_;
    public:

       /**
       * @brief Construct object.
       * @method HardAI
       * @param  c                farba hráča
       * @param  logic            ukazateľ na aktuálnu GameLogic
       * @param  randomness       0 - bez náhody, 1 - plne náhodné, (0,1) - náhodne náhodné
       */
        HardAI(Color c, const GameLogic& logic, double randomness = 1);

       /**
       * Deštruktor objectu.
       * @method ~HardAI
       */
        ~HardAI(){}

        /**
         * @brief Rozlíš medzi hrajúcim človekom a počítačom.
         * @method IsAi
         * @return True
         */
        virtual bool IsAi() const override { return true; }

        /**
         * @brief AI is vyberie svoj ťah.
         * @method Play
         * @return Súradníce, ktoré AI chce zahrať
         */
        virtual Coords Play() override;

    private:
        int Alphabeta(unsigned depth, int alpha, int beta, bool me, const GameLogic& old);
    };

}


#endif //OTHELLO_AI_HH
