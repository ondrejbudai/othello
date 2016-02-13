//
// Created by ondra on 11.2.16.
//

#ifndef OTHELLO_MAINGAME_HH
#define OTHELLO_MAINGAME_HH

#include "Player.hh"
#include "GameBoard.hh"
#include "GameLogic.hh"

namespace othello {


    class MainGame {
    private:
        GameBoard board_;
        Player players_[2];
        Color current_player_ = Color::WHITE;
        // frozen stuff
    public:
        MainGame(unsigned size) : board_{size} {};

        void event(unsigned x, unsigned y); // event funkce

        Color getCurrentPlayer() const { return current_player_; }

        const GameBoard &getBoard() {return board_;}
        
        void printGameBoard() const;//Zobrazi hraciu plochu na terminal
        
        void initPlayers() {}

    };
}


#endif //OTHELLO_MAINGAME_HH
