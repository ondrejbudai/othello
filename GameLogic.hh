//
// Created by matej on 11.2.16.
//

#ifndef OTHELLO_GAMELOGIC_HH
#define OTHELLO_GAMELOGIC_HH

#include "Player.hh"
#include "GameBoard.hh"


namespace othello {

    void play(unsigned x, unsigned y, Color playing);

    void initPlayers(); // struktura do parametru potom

    bool isMoveValid(unsigned x, unsigned y, Color addingColor, std::vector<Coords>& toChange, const GameBoard &board_);

    bool isEnd(const GameBoard &board_);
}


#endif //OTHELLO_GAMELOGIC_HH
