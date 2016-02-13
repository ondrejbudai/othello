//
// Created by ondra on 11.2.16.
//

#ifndef OTHELLO_MAINGAME_HH
#define OTHELLO_MAINGAME_HH

#include <memory>
#include "Player.hh"
#include "AI.hh"
#include "GameBoard.hh"
#include "GameLogic.hh"

namespace othello {

    enum class PlayerType {
        HUMAN, AI
    };


    class MainGame {
    private:
        GameLogic logic_;
        std::vector<std::unique_ptr<Player>> players_;
        int current_player_num = 0;
        // frozen stuff
    public:
        MainGame(unsigned size, PlayerType white, PlayerType black);

        void event(unsigned x, unsigned y); // event funkce

        Color getCurrentPlayerColor() { return players_[current_player_num]->getColor(); }

        void printGameBoard() const;//Zobrazi hraciu plochu na terminal

        bool isEnd() const;

    };
}


#endif //OTHELLO_MAINGAME_HH
