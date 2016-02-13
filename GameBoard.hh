//
// Created by ondra on 11.2.16.
//

#ifndef OTHELLO_GAMEBOARD_HH
#define OTHELLO_GAMEBOARD_HH

#include<vector>

namespace othello {

    using Coords = std::pair<unsigned, unsigned>;

    enum class Color {
        BLACK, WHITE, RED
    };

    struct Field {
        Color piece_;
        bool occupied_;
        bool frozen_;
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

        bool isOccupied(const Coords& c) const { return isOccupied(c.first, c.second); }

        unsigned getSize() const { return size_; }

        std::vector<Coords> getNeighbours(unsigned x, unsigned y) const;

        Color GetColor(unsigned x, unsigned y) const;

        Color GetColor(const Coords& c) const { return GetColor(c.first, c.second); }
    };
}


#endif //OTHELLO_GAMEBOARD_HH
