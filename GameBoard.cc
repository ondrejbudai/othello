//
// Created by ondra on 11.2.16.
//

#include "GameBoard.hh"
#include <cassert>

namespace othello {

    GameBoard::GameBoard(unsigned size):size_(size) {
        assert(size % 2 == 0);
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
    
    int GameBoard::getColor(unsigned x, unsigned y){
        assert(x < size_ && y < size_);

        return board_[x][y].piece_==Color::BLACK?0:1;
    }
    
    void GameBoard::getNeighbours(unsigned x, unsigned y, std::vector<Field> &fields){
        int xj = -1;
        int yj = -1;
        int xf =  1;
        int yf =  1;
        if (x == 0)       xj = 0;
        if (x == size_-1) xf = 0;
        if (y == 0)       yj = 0;
        if (y == size_-1) yf = 0;
        for (int i = xj; xj <= xf; i++)
            for (int j = yj; j <= yf; j++)
                fields.push_back(board_[i][j]);
    }
}

