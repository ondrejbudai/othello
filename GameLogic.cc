#include "GameLogic.hh"
#include <iostream>

namespace othello {

    inline Color GetOppositeColor(Color myColor) {
        return myColor == othello::Color::BLACK ? othello::Color::WHITE : othello::Color::BLACK;
    }


    /// x, y su suradnice
    //adding color je farba kamena, ktory chceme pridat
    //toChange je referencia na vektor parov, ktory naplnime vsetkymi poziciami, ktore sa maju
    //zmenit
    bool isMoveValid(unsigned x, unsigned y, Color addingColor, std::vector<Coords>& toChange,const GameBoard &board_) {

        Color oppositeColor = GetOppositeColor(addingColor);

        //zistime ci dava na volne policko
        if (board_.isOccupied(x, y))
            return false;//obsadene policko
        std::vector<Coords> fields = board_.getNeighbours(x, y);

        //zo vsetkych susednych vytriedime len tie, ktore su obsadene superom
        std::vector<Coords> oppositeFields;
        for (auto const& fld: fields) {
            if (board_.isOccupied(fld) && board_.GetColor(fld) == oppositeColor)
                oppositeFields.push_back(fld);
        }

        //ak sme nic nenasli, invalidny tah
        if (oppositeFields.empty())
            return false;

        //pre kazdy najdeny kamen zistime ci existuje cesta a pridam vsetky kamene z cesty do
        for (auto const& fld: oppositeFields) {
            int deltaX = fld.first - x; //smer posuvania x
            int deltaY = fld.second - y; //smer posuvania y
            int pomX = x;
            int pomY = y;
            std::vector<Coords> possibleChanges;
            while (true) {
                pomX += deltaX;
                pomY += deltaY;
                //ak sme sa dostali mimo pole
                if (pomX < 0 || pomX >= int(board_.getSize()) || pomY < 0 || pomY >= int(board_.getSize()))
                    break;
                Coords candidate{pomX, pomY};
//                Field candidate = board_.GetField(pomX, pomY);
                //ak dane poliecko nie je obsadene, nie je to kandidat
                if (!board_.isOccupied(candidate))
                    break;
                //ak sme nasli svoju farbu a mame aspon jednu superovu medzitym
                if (board_.GetColor(candidate) == addingColor && !possibleChanges.empty()) {
                    toChange.insert(end(toChange), begin(possibleChanges), end(possibleChanges));
                    break;
                }
                //ak sme nasli nas kamen, ale nic medzi nim
                if (board_.GetColor(candidate) == addingColor && possibleChanges.empty())
                    break;       
                //ak patri field superovy
                if (board_.GetColor(candidate) == oppositeColor)
                    possibleChanges.push_back(candidate);
            }

        }
        //DUPLICITY v toChange
        if (toChange.empty())
            return false;

        return true;
    }

    bool isEnd(const GameBoard &board_) {

        // najdi vsechna volna policka
        std::vector<Coords> emptyFields;
        for (unsigned x = 0; x < board_.getSize(); ++x) {
            for (unsigned y = 0; y < board_.getSize(); ++y) {
                if (!board_.isOccupied(x, y))
                    emptyFields.emplace_back(x, y);
            }
        }

        if (emptyFields.empty())
            return true;

        // projdi vsechny, pokud je alespon pro jednoho hrace mozny tah, hra nekonci
        std::vector<Coords> dummy;
        for (const auto& f : emptyFields) {
            if (isMoveValid(f.first, f.second, Color::WHITE, dummy, board_) ||
                isMoveValid(f.first, f.second, Color::BLACK, dummy, board_))
                return false;
        }

        return true;
    }
}

