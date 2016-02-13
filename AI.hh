//
// Created by ondra on 11.2.16.
//

#ifndef OTHELLO_AI_HH
#define OTHELLO_AI_HH

#include "Player.hh"
#include "GameBoard.hh"

namespace othello {


    class AI : public Player {
    public:
    public:
        virtual bool isAi() override { return true; }

        virtual Coords play(const GameBoard& board);
    };

}


#endif //OTHELLO_AI_HH
