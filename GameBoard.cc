//
// Created by ondra on 11.2.16.
//

#include "GameBoard.hh"
#include <cassert>
#include <iostream>

namespace othello {

    GameBoard::GameBoard(unsigned size):size_(size) {
        assert(size % 2 == 0);
        for (unsigned i = 0; i < size; i++){
            std::vector<Field> newRow;
            for (unsigned j = 0; j < size; j++){
                newRow.push_back(Field{Color::RED, false});
            }
            board_.push_back(newRow);
        }
        unsigned middle = size / 2;
        this->setPiece(middle, middle, Color::BLACK);
        this->setPiece(middle-1, middle-1, Color::BLACK);
            
        this->setPiece(middle-1, middle, Color::WHITE);
        this->setPiece(middle, middle-1, Color::WHITE);
    }

    void GameBoard::CountScore(int &black, int &white) const{
        for (unsigned i = 0; i < size_; i++)
            for (unsigned j = 0; j < size_; j++)
                if (isOccupied(i,j)){
                    if (GetColor(i,j) == Color::BLACK)
                        black++;
                    else
                        white++;
                }
    }


    const Field& GameBoard::GetField(unsigned x, unsigned y) const {
        assert(x < size_ && y < size_);
        return board_[x][y];
    }

    void GameBoard::setPiece(unsigned x, unsigned y, Color c) {
        assert(x < size_ && y < size_);
        board_[x][y].occupied_ = true;
        board_[x][y].piece_ = c;
    }

    bool GameBoard::isOccupied(unsigned x, unsigned y) const {
        assert(x < size_ && y < size_);
        return board_[x][y].occupied_;
    }


    std::vector<Coords> GameBoard::getNeighbours(unsigned x, unsigned y) const {
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

    Color GameBoard::GetColor(unsigned x, unsigned y) const {
        assert(x < size_ && y < size_);
        return board_[x][y].piece_;
    }
    
    
    void GameBoard::copyBoard(Board &toThis){
        toThis = board_;
    }
}

