//
// Created by ondra on 11.2.16.
//

#ifndef OTHELLO_GAMELOGIC_HH
#define OTHELLO_GAMELOGIC_HH

#include "GameBoard.hh"

namespace othello {

    class GameLogic {
    private:
        GameBoard board_;
        Color current_player_;
        // frozen stuff
    public:
        GameLogic(unsigned size) : board_{size} { }

        void play(unsigned x, unsigned y, Color playing);

        Color getCurrentPlayer() { return current_player_; }
        // funkce pro AI, Human, podminka vitezstvi, validita, atd...
    };
}


#endif //OTHELLO_GAMELOGIC_HH
