//
// Created by ondra on 11.2.16.
//

#ifndef OTHELLO_AI_HH
#define OTHELLO_AI_HH

#include <random>
#include "Player.hh"
#include "GameBoard.hh"

namespace othello {

    class AI : public Player {
    private:
        std::mt19937 random;
        double randomness_;
    public:
        AI(Color c, const GameLogic& logic, double randomness = 1);

        virtual bool isAi() const override { return true; }

        virtual Coords play() override;
    };

}


#endif //OTHELLO_AI_HH
