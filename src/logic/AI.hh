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

    class AI : public Player {
    private:
        std::mt19937 random_;
        double randomness_;
    public:
        AI(Color c, const GameLogic& logic, double randomness = 1);

        ~AI(){}

        virtual bool IsAi() const override { return true; }

        virtual Coords Play() override;
    };

}


#endif //OTHELLO_AI_HH
