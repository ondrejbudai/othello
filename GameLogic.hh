//
// Created by matej on 11.2.16.
//

#ifndef OTHELLO_GAMELOGIC_HH
#define OTHELLO_GAMELOGIC_HH

#include "GameBoard.hh"


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
    };
}


#endif //OTHELLO_GAMELOGIC_HH
