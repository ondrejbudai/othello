/**
 * @file
 * @brief Herní logika.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#include "GameLogic.hh"
#include "MainGame.hh"
#include <cassert>
#include <algorithm>
#include <map>

namespace othello {

    /// x, y su suradnice
    //adding color je farba kamena, ktory chceme pridat
    //toChange je referencia na vektor parov, ktory naplnime vsetkymi poziciami, ktore sa maju
    //zmenit
    std::vector<Coords> GameLogic::PrepareTurn(unsigned x, unsigned y, Color addingColor) const {

        Color oppositeColor = GetOppositeColor(addingColor);
        std::vector<Coords> toChange;

        //zistime ci dava na volne policko
        if (board_.GetField(x, y).IsOccupied())
            return toChange;
        std::vector<Coords> fields = board_.GetNeighbours(x, y);

        //zo vsetkych susednych vytriedime len tie, ktore su obsadene superom
        std::vector<Coords> oppositeFields;
        for (auto const& fld: fields) {
            Color c;
            bool occupied = board_.GetField(fld).GetStatus(c);
            if (occupied && c == oppositeColor)
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
                if (pomX < 0 || pomX >= int(board_.GetSize()) || pomY < 0 || pomY >= int(board_.GetSize()))
                    break;
//                Field candidate = board_.GetField(pomX, pomY);
                //ak dane poliecko nie je obsadene, nie je to kandidat
                Color col;
                bool occupied = board_.GetField(pomX, pomY).GetStatus(col);
                if (!occupied)
                    break;
                //ak sme nasli svoju farbu a mame aspon jednu superovu medzitym
                if (col == addingColor && !possibleChanges.empty()) {
                    toChange.insert(end(toChange), begin(possibleChanges), end(possibleChanges));
                    break;
                }
                //ak sme nasli nas kamen, ale nic medzi nim
                if (col == addingColor && possibleChanges.empty())
                    break;
                //ak patri field superovy
                if (col == oppositeColor)
                    possibleChanges.push_back({static_cast<unsigned>(pomX), static_cast<unsigned>(pomY)});
            }

        }
        if (!toChange.empty())
            toChange.push_back({x, y});

        return toChange;
    }

    void GameLogic::CommitTurn(const std::vector<Coords>& pieces, Color player) {
        for (auto const& fld: pieces) {
            board_.GetField(fld).SetColor(player);
        }
    }

    // void GameLogic::setGameBoard(const GameBoard& t){
    //   board_.setBoard(t.GetBoard());
    // }

    std::pair<unsigned, unsigned> GameLogic::GetScore() const {
        std::pair<unsigned, unsigned> score{0, 0};

        for(const auto& f: board_){
            Color col;
            bool occupied = f.GetStatus(col);
            if(!occupied)
                continue;
            if(col == Color::BLACK){
                score.first++;
            } else {
                score.second++;
            }
        }

        return score;
    }

    std::multimap<unsigned, Coords> GameLogic::GetValidMoves(Color current) const{
        std::vector<Coords> emptyFields;
        // najdi vsechna volna policka
        for (unsigned x = 0; x < board_.GetSize(); ++x) {
            for (unsigned y = 0; y < board_.GetSize(); ++y) {
                if (!board_.GetField(x, y).IsOccupied())
                    emptyFields.emplace_back(x, y);
            }
        }
        if(emptyFields.empty()){
            return {};
        }

        // projdi vsechny, uloz do validMoves s indexem pocet upravenych kamenu
        std::multimap<unsigned, Coords> validMoves;
        for (const auto& f : emptyFields) {
            unsigned changedPieces = unsigned(PrepareTurn(f.GetX(), f.GetY(), current).size());
            if (changedPieces > 0)
                validMoves.insert({changedPieces, f});
        }
        return validMoves;
    }

    void GameLogic::MarkPossibleMoves(Color current){

        std::multimap<unsigned, Coords> validMoves = GetValidMoves(current);
        for (auto const& fld: validMoves) {
            board_.GetField(fld.second).SetPossible(true);
        }
    }

    void GameLogic::ClearFlags(){
        for(auto& f: board_)
            f.SetPossible(false);
    }

    //Urcuje ci moze hrat hrac zadany parametrom
    bool GameLogic::CanPlay(Color color) const {
        return GetValidMoves(color).size() != 0;
    }
}
