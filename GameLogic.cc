#include "GameLogic.hh"
#include "MainGame.hh"

namespace othello {

    /// x, y su suradnice
    //adding color je farba kamena, ktory chceme pridat
    //toChange je referencia na vektor parov, ktory naplnime vsetkymi poziciami, ktore sa maju
    //zmenit
    std::vector<Coords> GameLogic::prepareTurn(unsigned x, unsigned y, Color addingColor) const {

        Color oppositeColor = GetOppositeColor(addingColor);
        std::vector<Coords> toChange;

        //zistime ci dava na volne policko
        if (board_.isOccupied(x, y))
            return toChange;
        std::vector<Coords> fields = board_.getNeighbours(x, y);

        //zo vsetkych susednych vytriedime len tie, ktore su obsadene superom
        std::vector<Coords> oppositeFields;
        for (auto const& fld: fields) {
            if (board_.isOccupied(fld) && board_.GetColor(fld) == oppositeColor)
                oppositeFields.push_back(fld);
        }

        //ak sme nic nenasli, invalidny tah
        if (oppositeFields.empty())
            return toChange;

        //pre kazdy najdeny kamen zistime ci existuje cesta a pridam vsetky kamene z cesty do
        for (auto const& fld: oppositeFields) {
            int deltaX = fld.GetX() - x; //smer posuvania x
            int deltaY = fld.GetY() - y; //smer posuvania y
            int pomX = x;
            int pomY = y;
            std::vector<Coords> possibleChanges;
            while (true) {
                pomX += deltaX;
                pomY += deltaY;
                //ak sme sa dostali mimo pole
                if (pomX < 0 || pomX >= int(board_.getSize()) || pomY < 0 || pomY >= int(board_.getSize()))
                    break;
                Coords candidate{unsigned(pomX), unsigned(pomY)};
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
        if (!toChange.empty())
            toChange.push_back({x, y});

        return toChange;
    }

    void GameLogic::commitTurn(const std::vector<Coords>& pieces, Color player) {
        for (auto const& fld: pieces) {
            board_.setPiece(fld.GetX(), fld.GetY(), player);
        }
    }


    std::pair<unsigned, unsigned> GameLogic::getScore() const {
        std::pair<unsigned, unsigned> score{0, 0};

        for (unsigned i = 0; i < board_.getSize(); i++) {
            for (unsigned j = 0; j < board_.getSize(); j++) {
                if (!board_.isOccupied(i, j)) continue;
                if (board_.GetColor(i, j) == Color::BLACK)
                    score.first++;
                else
                    score.second++;
            }
        }


        return score;
    }
}

