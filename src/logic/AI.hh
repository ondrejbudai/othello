/**
 * @file
 * @brief Umělá inteligence pouze s predikcí na jeden tah dopředu.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_AI_HH
#define OTHELLO_AI_HH

#include <random>
#include "Player.hh"
#include "GameBoard.hh"

namespace othello {

    /**
     * Varianta hráča ovládaného počítačom.
     * @class AI
     */
    class AI : public Player {
    private:
        /**
         * Mersanne-twister generátor.
         * @var random_
         */
        std::mt19937 random_;

        /**
         * Level obtiažnosti.
         * @var random_
         */
        double randomness_;
    public:

       /**
       * Construct object.
       * @method AI
       * @param  c                farba hráča
       * @param  logic            ukazateľ na aktuálnu GameLogic
       * @param  randomness       0 - bez náhody, 1 - plne náhodné, (0,1) - náhodne náhodné
       */
        AI(Color c, const GameLogic& logic, double randomness = 1);

       /**
       * Deštruktor objectu.
       * @method ~AI
       */
        ~AI(){}

        /**
         * Rozlíš medzi hrajúcim človekom a počítačom.
         * @method IsAi
         * @return True
         */
        virtual bool IsAi() const override { return true; }

        /**
         * AI is vyberie svoj ťah.
         * @method Play
         * @return Súradníce, ktoré AI chce zahrať
         */
        virtual Coords Play() override;
    };

}


#endif //OTHELLO_AI_HH
