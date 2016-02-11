//
// Created by ondra on 11.2.16.
//

#ifndef OTHELLO_PLAYER_HH
#define OTHELLO_PLAYER_HH

#include<string>
#include "GameBoard.hh"

namespace othello {

    class Player {
    private:
        Color color_;
        std::string name;
    public:
        virtual void play() { }

        virtual bool isAi() { return false; }
    };
}

#endif //OTHELLO_PLAYER_HH
