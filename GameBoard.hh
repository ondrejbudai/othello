//
// Created by ondra on 11.2.16.
//

#ifndef OTHELLO_GAMEBOARD_HH
#define OTHELLO_GAMEBOARD_HH

#include<vector>

namespace othello {

    enum class Color {
        BLACK, WHITE
    };

    struct Field {
        Color piece_;
        bool occupied_;
        bool frozen_;
        unsigned x_;
        unsigned y_;
    };

    class GameBoard {
    private:

        using Board = std::vector<std::vector<Field>>;
        Board board_;
        const unsigned size_;

    public:
        GameBoard(unsigned size);

        const Field& GetField(unsigned x, unsigned y) const;

        void setPiece(unsigned x, unsigned y, Color c);

        void setFrozen(unsigned x, unsigned y, bool f);

        bool isOccupied(unsigned x, unsigned y) const;

        unsigned getSize() const { return size_; }

        std::vector<Field> getNeighbours(unsigned x, unsigned y) const;
    };
}


#endif //OTHELLO_GAMEBOARD_HH
