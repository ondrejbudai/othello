/**
 * @file
 * @brief Kontejner pro herní desku.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_GAMEBOARD_HH
#define OTHELLO_GAMEBOARD_HH

#include<vector>
#include<memory>
#include<iostream>

#include "Field.hh"

namespace othello {
    /**
     * @brief Súradnice.
     * @class Coords
     */
    class Coords {
    private:
        /**
         * @brief Súradnica x.
         * @var x_
         */
        unsigned x_;

        /**
         * @brief Súradnica y.
         * @var y_
         */
        unsigned y_;
    public:
        /**
         * @brief Konštruktor súradníc
         * @method Coords
         * @arg x Súradnica x.
         * @arg y Súradnica y.
         */
        Coords(unsigned x, unsigned y) : x_{x}, y_{y} { }

        /**
         * @brief Vráti x-ovú časť súradnice.
         * @method GetX
         * @return x-ová časť súradnice.
         */
        unsigned GetX() const { return x_; }

        /**
         * @brief Vráti y-ovú časť súradnice.
         * @method GetY
         * @return y-ová časť súradnice.
         */
        unsigned GetY() const { return y_; }
    };

    /**
     * @brief Vrať opačnou barvu
     * @param  my_color Barva na obrácení
     * @return Opačná barva
     */
    inline Color GetOppositeColor(Color my_color) {
        return my_color == Color::BLACK ? Color::WHITE : Color::BLACK;
    }

    /**
     * @brief Hracia doska.
     * @class GameBoard
     */
    class GameBoard {
    private:
        /**
         * @brief Hracia doska je vektor vektorov políčok.
         * @typedef Board
         */
        using Board = std::vector<std::vector<Field>>;

        /**
         * @brief Hracia doska.
         * @var board_
         */
        Board board_;

        /**
         * @brief Veľkosť hracej dosky.
         * @var size_
         */
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
        /**
         * @brief Konštruktor hracej dosky.
         * @method GameBoard
         * @arg size  Veĺkosť hracej dosky.
         */
        GameBoard(unsigned size);

        /**
         * @brief Vráti hraciu dosku.
         * @method GetBoard
         * @return Referencia na hraciu dosku.
         */
        const Board& GetBoard() const {return board_;}

        /**
         * @brief Vráti políčko z hracej dosky, určené súradnicami.
         * @method GetField
         * @param  x        X-ová súradnica.
         * @param  y        Y-ová súradnica.
         * @return          Referenica na vybrané políčko.
         */
        Field& GetField(unsigned x, unsigned y);

        /**
         * @brief Vráti políčko z hracej dosky, určené súradnicami.
         * @method GetField
         * @param  x        X-ová súradnica.
         * @param  y        Y-ová súradnica.
         * @return          Konštantná referenica na vybrané políčko.
         */
        const Field& GetField(unsigned x, unsigned y) const;

        /**
         * @brief Vráti políčko z hracej dosky, určené súradnicami.
         * @method GetField
         * @param  c        súradnice bodu.
         * @return          Referenica na vybrané políčko.
         */
        Field& GetField(Coords c);

        /**
         * @brief Vráti políčko z hracej dosky, určené súradnicami.
         * @method GetField
         * @param  c        súradnice bodu.
         * @return          Konštantná referenica na vybrané políčko.
         */
        const Field& GetField(Coords c) const;

        /**
         * @brief Vráti veľkosť hracej dosky.
         * @method GetSize
         * @return Veľkosť hracej dosky.
         */
        unsigned GetSize() const { return size_; }

        /**
         * @brief Vráti všetky susediace políčka.
         * @method GetNeighbours
         * @arg x   X-ová súradnica.
         * @arg y   Y-ová súradnica.
         * @return  Všetky susediace políčka.
         */
        std::vector<Coords> GetNeighbours(unsigned x, unsigned y) const;

        /**
         * @brief Zapíše hraciu plochu do súboru.
         * @method Print
         * @param  os    pripravený výstupný súbor.
         */
        void Print(std::ostream& os) const;//Zobrazi hraciu plochu na terminal

        /**
         * @brief Nastaví hraciu plochu.
         * @method SetBoard
         * @param  b        Vzor plochy, ktorá sa má nastaviť.
         */
        void SetBoard(Board b) {board_ = b;}

        /**
         * @brief Nastaví hraciu plochu.
         * @method SetBoard
         * @param  b        Vzor plochy, ktorá sa má nastaviť.
         */
        void SetBoard(const GameBoard &b) {board_ = b.board_;}

        iterator begin(){return iterator{&board_};};
        const_iterator begin() const {return const_iterator{&board_};};
        iterator end(){return iterator{&board_, true};};
        const_iterator end() const {return const_iterator{&board_, true};};
    };
}


#endif //OTHELLO_GAMEBOARD_HH
