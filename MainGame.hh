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
        Color current_player_ = Color::WHITE;
        Player players_[2];
        // frozen stuff
    public:
        MainGame(unsigned size):board_{size}{}; 
        
        void play(unsigned x, unsigned y, Color playing);

        void initPlayers(); // struktura do parametru potom

        void event(unsigned x, unsigned y); // event funkce

        void printGameBoard() const;//Zobrazi hraciu plochu na terminal

        Color getCurrentPlayer() const { return current_player_; }
        
        bool isMoveValid(unsigned x, unsigned y, Color addingColor, std::vector<std::pair<int,int> > &toChange);
    };
}


#endif //OTHELLO_MAINGAME_HH
