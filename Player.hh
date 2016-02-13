//
// Created by ondra on 11.2.16.
//

#ifndef OTHELLO_PLAYER_HH
#define OTHELLO_PLAYER_HH

#include<string>
#include "GameBoard.hh"
#include <iostream>

#define UNUSED __attribute__((unused))

namespace othello {

    class Player {
    protected:
        Color color_;
        std::string name;
    public:
        Player(Color c) :color_(c){}
        virtual void play(UNUSED const GameBoard &board,UNUSED Coords &thisMove){}

        virtual Color getColor() {return color_;}

        virtual bool isAi() { return false; }
    };
}

#endif //OTHELLO_PLAYER_HH
