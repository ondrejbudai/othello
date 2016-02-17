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
                newRow.push_back(Field{Color::RED, false, false});
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

    void GameBoard::UnfreezeAll() {
        for (unsigned x = 0; x < size_; ++x)
            for (unsigned y = 0; y < size_; ++y)
                setFrozen(x,y,false);
    }

    void GameBoard::SetRandomToFreeze(unsigned n){
        std::vector<Coords> setFields;

        //najdem vsetky obsadene
        for (unsigned x = 0; x < size_; ++x) {
            for (unsigned y = 0; y < size_; ++y) {
                if (isOccupied(x, y))
                    setFields.emplace_back(x, y);
            }
        }
        //TODO - podmienky na to, cize nieje n vacisealebo rovne ako size()...
        //vygenerujeme n nahodych cisel a tolko zmrazime
        for (unsigned i = 0; i < n; i++){
            int randomFieldIndex = rand() % int(setFields.size());
            setFrozen(setFields[randomFieldIndex], true);
            setFields.erase(setFields.begin()+randomFieldIndex);//sorry
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

    void GameBoard::setFrozen(unsigned x, unsigned y, bool f) {
        assert(x < size_ && y < size_);
        board_[x][y].frozen_ = f;
        
    }

    bool GameBoard::isFrozen(const Coords& c)const{
        unsigned x = c.GetX();
        unsigned y = c.GetY();
        assert(x < size_ && y < size_);
        return board_[x][y].frozen_;
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
}

