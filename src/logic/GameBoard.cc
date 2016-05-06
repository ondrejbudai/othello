/**
 * @file
 * @brief Kontejner pro herní desku.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#include "GameBoard.hh"
#include <cassert>
#include <iostream>

namespace othello {

    GameBoard::GameBoard(unsigned size):size_(size) {
        assert(size % 2 == 0);
        for (unsigned i = 0; i < size; i++){
            std::vector<Field> newRow;
            for (unsigned j = 0; j < size; j++){
                newRow.push_back(Field{});
            }
            board_.push_back(newRow);
        }
        unsigned middle = size / 2;

        GetField(middle, middle).SetColor(Color::BLACK);
        GetField(middle - 1, middle - 1).SetColor(Color::BLACK);

        GetField(middle - 1, middle).SetColor(Color::WHITE);
        GetField(middle, middle - 1).SetColor(Color::WHITE);
    }

    Field& GameBoard::GetField(unsigned x, unsigned y) {
        assert(x < size_ && y < size_);
        return board_[x][y];
    }

    const Field& GameBoard::GetField(unsigned x, unsigned y) const {
        assert(x < size_ && y < size_);
        return board_[x][y];
    }

    Field& GameBoard::GetField(Coords c) {
        assert(c.GetX() < size_ && c.GetY() < size_);
        return board_[c.GetX()][c.GetY()];
    }

    const Field& GameBoard::GetField(Coords c) const {
        assert(c.GetX() < size_ && c.GetY() < size_);
        return board_[c.GetX()][c.GetY()];
    }

    std::vector<Coords> GameBoard::GetNeighbours(unsigned x, unsigned y) const {
        assert(x < size_ && y < size_);
        std::vector<Coords> fields;
        int xj = -1;
        int yj = -1;
        int xf =  1;
        int yf =  1;
        if (x == 0)       xj = 0;
        if (x == size_-1) xf = 0;
        if (y == 0)       yj = 0;
        if (y == size_-1) yf = 0;
        for (int i = xj; i <= xf; i++)
            for (int j = yj; j <= yf; j++)
                fields.emplace_back(x + i, y + j);
        return fields;
    }

    void GameBoard::Print(std::ostream& os) const {//Zobrazi hraciu plochu na terminal

        os << "   ";
        for (unsigned i = 0; i < GetSize(); i++) {
            os << i;
            if (i < 10)
                os << " ";
        }
        os << std::endl;
        for (unsigned i = 0; i < GetSize(); i++) {
            if (i < 10)
                os << " ";
            os << i << " ";
            for (unsigned j = 0; j < GetSize(); j++) {
                Color col;
                bool occupied = GetField(i, j).GetStatus(col);
                if (occupied)
                    os << (col == Color::BLACK ? "\u25CB" : "\u25CD") << " ";
                else
                    os << "  ";
            }
            os << std::endl;
        }
    }
}
