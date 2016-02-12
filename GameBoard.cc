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
                newRow.push_back(Field{Color::BLACK,false,false,i,j});
            //board_.push_back(std::vector<Field>(size,{Color::BLACK,false,false}));	
            }
            board_.push_back(newRow);
        }
        unsigned middle = size / 2;
        this->setPiece(middle, middle, Color::BLACK);
        this->setPiece(middle-1, middle-1, Color::BLACK);
            
        this->setPiece(middle-1, middle, Color::WHITE);
        this->setPiece(middle, middle-1, Color::WHITE);
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

    void GameBoard::setFrozen(unsigned x, unsigned y, bool f) {
        assert(x < size_ && y < size_);
        board_[x][y].frozen_ = f;
        
    }


    bool GameBoard::isOccupied(unsigned x, unsigned y) const {
        assert(x < size_ && y < size_);
        return board_[x][y].occupied_;
    }


    std::vector<Field>GameBoard::getNeighbours(unsigned x, unsigned y) const {
        std::vector<Field> fields;
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
                fields.push_back(board_[x+i][y+j]);
        return fields;
    }
}

