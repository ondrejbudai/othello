//
// Created by ondra on 11.2.16.
//

#ifndef OTHELLO_GAMEBOARD_HH
#define OTHELLO_GAMEBOARD_HH

#include<vector>

namespace othello {

    class Coords {
    private:
        unsigned x_;
        unsigned y_;
    public:
        Coords(unsigned x, unsigned y) : x_{x}, y_{y} { }

        unsigned GetX() const { return x_; }

        unsigned GetY() const { return y_; }
    };

    enum class Color {
        BLACK, WHITE, RED
    };

    inline Color GetOppositeColor(Color myColor) {
        return myColor == Color::BLACK ? Color::WHITE : Color::BLACK;
    }

    struct Field {
        Color piece_;
        bool occupied_;
    };

    class GameBoard {
    private:

        using Board = std::vector<std::vector<Field>>;
        Board board_;
        const unsigned size_;

    public:
        GameBoard(unsigned size);

        void copyBoard(Board &toThis);

        const Board& GetBoard() const {return board_;}

        const Field& GetField(unsigned x, unsigned y) const;

        void setPiece(unsigned x, unsigned y, Color c);

        bool isOccupied(unsigned x, unsigned y) const;

        bool isOccupied(const Coords& c) const { return isOccupied(c.GetX(), c.GetY()); }

        unsigned getSize() const { return size_; }

        std::vector<Coords> getNeighbours(unsigned x, unsigned y) const;

        Color GetColor(unsigned x, unsigned y) const;

        Color GetColor(const Coords& c) const { return GetColor(c.GetX(), c.GetY()); }

        void setBoard(std::vector<std::vector<Field>> t){ board_ = t;}
    };
}


#endif //OTHELLO_GAMEBOARD_HH
