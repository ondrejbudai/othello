//
// Created by ondra on 11.2.16.
//

#ifndef OTHELLO_MAINGAME_HH
#define OTHELLO_MAINGAME_HH

#include "GameLogic.hh"
#include "Player.hh"


namespace othello {
    class MainGame {
    private:
        GameLogic game_logic_;
        Player players_[2];
    public:
        MainGame(unsigned size) : game_logic_{size} { }

        void initPlayers(); // struktura do parametru potom

        void event() { } // event funkce
    };
}


#endif //OTHELLO_MAINGAME_HH
