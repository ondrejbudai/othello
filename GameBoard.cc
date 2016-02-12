//
// Created by ondra on 11.2.16.
//

#include "GameBoard.hh"
#include <cassert>

namespace othello {

    GameBoard::GameBoard(unsigned size) {
        assert(size % 2 == 0);
        size_ = size;
        for (unsigned i = 0; i < size; i++){
            board_.push_back(std::vector<Field>(size,{Color::BLACK,false,false}));	
            
        }
        int middle = size / 2;
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

    
    bool GameBoard::isOccupied(unsigned x, unsigned y){
        assert(x < size_ && y < size_);
        return board_[x][y].occupied_;
    }
}

