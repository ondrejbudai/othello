//
// Created by ondra on 11.2.16.
//

#ifndef OTHELLO_GAMEBOARD_HH
#define OTHELLO_GAMEBOARD_HH

#include<vector>
#include<memory>
#include<iostream>

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

        template <typename T, typename C> class iterator_template {
            public:
                typedef iterator_template self_type;
                typedef T value_type;
                typedef T& reference;
                typedef T* pointer;
                typedef std::forward_iterator_tag iterator_category;
                typedef int difference_type;

                iterator_template(C* ptr, bool end = false) : ptr_{ptr}, size_{ptr->size()} {if(end) {y_ = size_;} else {y_ = 0;}}
                self_type operator++() { self_type i = *this; x_++; if(x_ >= size_){ y_++; x_ = 0;} return i; }
                self_type operator++(int) { x_++; if(x_ >= size_){ y_++; x_ = 0;} return *this; }
                reference operator*() { return (*ptr_)[x_][y_]; }
                pointer operator->() { return &(*ptr_)[x_][y_]; }
                bool operator==(const self_type& b) { return ptr_ == b.ptr_ && x_ == b.x_ && y_ == b.y_; }
                bool operator!=(const self_type& b) { return ptr_ != b.ptr_ || x_ != b.x_ || y_ != b.y_; }
            private:
                C* ptr_;
                size_t x_ = 0, y_, size_;
        };

        using iterator = iterator_template<Field, Board>;
        using const_iterator = iterator_template<const Field, const Board>;

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

        iterator begin(){return iterator{&board_};};
        const_iterator begin() const {return const_iterator{&board_, true};};
        iterator end(){return iterator{&board_};};
        const_iterator end() const {return const_iterator{&board_, true};};
    };
}


#endif //OTHELLO_GAMEBOARD_HH
