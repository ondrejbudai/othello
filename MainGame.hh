//
// Created by ondra on 11.2.16.
//

#ifndef OTHELLO_MAINGAME_HH
#define OTHELLO_MAINGAME_HH

#include "Player.hh"
#include "GameBoard.hh"


namespace othello {


    class MainGame {
    private:
        GameBoard board_;
        Color current_player_;
        Player players_[2];
        // frozen stuff
    public:
        MainGame(unsigned size):board_{size}{}; 
        
        void play(unsigned x, unsigned y, Color playing);

        void initPlayers(); // struktura do parametru potom

        Color event(unsigned x, unsigned y); // event funkce

        void printGameBoard();//Zobrazi hraciu plochu na terminal
        
        Color getCurrentPlayer() { return current_player_; }
    };
}


#endif //OTHELLO_MAINGAME_HH
