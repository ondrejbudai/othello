/**
 * @file
 * @brief Umělá inteligence pouze s predikcí na jeden tah dopředu.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#include "AI.hh"
#include <iostream>
#include <map>
#include <cassert>

namespace othello {
    AI::AI(Color c, const GameLogic& logic, double randomness) : Player(c, logic), randomness_{randomness} {
        std::random_device rd;
        random_ = std::mt19937(rd());
    }

    Coords AI::Play() {
        std::vector<Coords> emptyFields;
        const GameBoard& board = logic_.GetBoard();

        // najdi vsechna volna policka
        for (unsigned x = 0; x < board.GetSize(); ++x) {
            for (unsigned y = 0; y < board.GetSize(); ++y) {
                if (!board.GetField(x, y).IsOccupied())
                    emptyFields.emplace_back(x, y);
            }
        }
        assert(!emptyFields.empty());


        // projdi vsechny, uloz do validMoves s indexem pocet upravenych kamenu
        std::multimap<unsigned, Coords> validMoves;
        for (const auto& f : emptyFields) {
            unsigned changedPieces = unsigned(logic_.PrepareTurn(f.GetX(), f.GetY(), color_).size());
            if (changedPieces > 0)
                validMoves.insert({changedPieces, f});
        }

        assert(!validMoves.empty());

        for (const auto& f : validMoves) {
            unsigned xV = f.second.GetX();
            unsigned yV = f.second.GetY();
            if (xV == 0) {
                if (yV == 0 || yV == board.GetSize() - 1)
                    return f.second;
            }
            else if (xV == board.GetSize() - 1) if (yV == 0 || yV == board.GetSize() - 1)
                return f.second;
        }

        unsigned maxOffset = unsigned(validMoves.size() * randomness_);
        auto p = validMoves.rbegin();
        if (maxOffset > 0) {
            unsigned offset = unsigned(random() % unsigned(validMoves.size() * randomness_));
            std::advance(p, offset);
        }

        auto itlow = validMoves.lower_bound(p->first);
        auto ithigh = validMoves.upper_bound(p->first);

        auto offset = random() % std::distance(itlow, ithigh);

        std::advance(itlow, offset);

        // map je serazena, vezmeme posledni prvek (na ktery ukazuje reverzni iterator)
        return itlow->second;
    }


}//namespace othello
