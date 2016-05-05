//
// Created by matej on 11.2.16.
//

#ifndef OTHELLO_GAMELOGIC_HH
#define OTHELLO_GAMELOGIC_HH

#include "GameBoard.hh"
#include <string>

namespace othello {
    class GameLogic {
    private:
        GameBoard board_;
    public:
        GameLogic(unsigned size) : board_{size} { }


        std::vector<Coords> prepareTurn(unsigned x, unsigned y, Color addingColor) const;

        void copyBoard(std::vector<std::vector<Field>>& toThis) {board_.copyBoard(toThis);};

        void commitTurn(const std::vector<Coords>& pieces, Color player);

        const GameBoard& getBoard() const { return board_; }

        std::pair<unsigned, unsigned> getScore() const;

        void setGameBoard(const GameBoard& t);

        void setGameBoard(std::vector<std::vector<Field>> y){ board_.setBoard(y);}

    };
}


#endif //OTHELLO_GAMELOGIC_HH
