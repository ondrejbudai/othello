/**
 * @file
 * @brief Umělá inteligence pouze s predikcí na jeden tah dopředu.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#include "HardAI.hh"
#include <iostream>
#include <map>
#include <cassert>

namespace othello {

    static const unsigned MAX_DEPTH = 4;

    HardAI::HardAI(Color c, const GameLogic& logic, double randomness) : Player(c, logic), randomness_{randomness} {
        std::random_device rd;
        random_ = std::mt19937(rd());
        std::cout << "Die!" << "\n";
    }

    // Coords HardAI::Play2() {
    //     const GameBoard& board = logic_.GetBoard();
    //     std::multimap<unsigned, Coords> validMoves;
    //     validMoves = logic_.GetValidMoves(color_);
    //     assert(!validMoves.empty());
    //
    //     for (const auto& f : validMoves) {
    //         unsigned xV = f.second.GetX();
    //         unsigned yV = f.second.GetY();
    //         if (xV == 0) {
    //             if (yV == 0 || yV == board.GetSize() - 1)
    //                 return f.second;
    //         }
    //         else if (xV == board.GetSize() - 1) if (yV == 0 || yV == board.GetSize() - 1)
    //             return f.second;
    //     }
    //
    //     unsigned maxOffset = unsigned(validMoves.size() * randomness_);
    //     auto p = validMoves.rbegin();
    //     if (maxOffset > 0) {
    //         unsigned offset = unsigned(random() % unsigned(validMoves.size() * randomness_));
    //         std::advance(p, offset);
    //     }
    //
    //     auto itlow = validMoves.lower_bound(p->first);
    //     auto ithigh = validMoves.upper_bound(p->first);
    //
    //     auto offset = random() % std::distance(itlow, ithigh);
    //
    //     std::advance(itlow, offset);
    //
    //     // map je serazena, vezmeme posledni prvek (na ktery ukazuje reverzni iterator)
    //     return itlow->second;
    // }

    int HardAI::Alphabeta(unsigned depth, int alpha, int beta, bool me, const GameLogic& old) {
    	int v;
    	if (depth == 0){
            auto score = old.GetScore();
            if(color_ == Color::BLACK){
                return score.first - score.second;
            } else {
                return score.second - score.first;
            }
        }
        Color current_color = me ? color_ : GetOppositeColor(color_);

        if(!old.CanPlay(current_color)){
            return me ? alpha : beta;
        }
        auto possible_moves = old.GetValidMoves(current_color);

    	if (me) {
    		v = std::numeric_limits<int>::min();
    		for (const auto& c: possible_moves) {
                GameLogic logic = old;
                logic.CommitTurn(logic.PrepareTurn(c.second.GetX(), c.second.GetY(), current_color), current_color);
    			v = std::max(v, Alphabeta(depth - 1, alpha, beta, false, logic));
    			alpha = std::max(alpha, v);
    			if (alpha >= beta)
    				break;
    		}
    		return v;
    	} else {
    		v = std::numeric_limits<int>::max();
    		for (const auto& c : possible_moves) {
                GameLogic logic = old;
                logic.CommitTurn(logic.PrepareTurn(c.second.GetX(), c.second.GetY(), current_color), current_color);
    			v = std::min(v, Alphabeta(depth - 1, alpha, beta, true, logic));
    			beta = std::min(beta, v);
    			if (alpha >= beta)
    				break;

    		}
    		return v;
    	}
    }

    Coords HardAI::Play() {
        auto moves = logic_.GetValidMoves(color_);
    	const Coords* best_coords = nullptr;
    	int best_score = std::numeric_limits<int>::min();
    	for (const auto& c : moves) {

            GameLogic logic = logic_;
            logic.CommitTurn(logic.PrepareTurn(c.second.GetX(), c.second.GetY(), color_), color_);
    		int a = Alphabeta(MAX_DEPTH, best_score, std::numeric_limits<int>::max(), false, logic);

            if(a >= best_score){
                best_coords = &c.second;
                best_score = a;
            }

    	}

        return *best_coords;
    }




}//namespace othello
