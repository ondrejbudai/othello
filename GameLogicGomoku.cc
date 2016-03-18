#include "GameLogicGomoku.hh"
#include "MainGame.hh"
#include <cassert>

namespace othello {

    Color GameLogic::isEnd() const {
        for (unsigned x = 0; x < board_.getSize(); ++x) {
            Color s = Color::RED;
            unsigned counter = 0;
            for (unsigned y = 0; y < board_.getSize(); ++y) {
                if (!board_.isOccupied(x, y)) {
                    s = Color::RED;
                    counter = 0;
                } else if (board_.GetColor(x, y) == s) {
                    counter++;
                } else {
                    counter = 1;
                }
                s = board_.GetColor(x, y);

                if (counter == 5) {
                    return s;
                }
            }
        }

        for (unsigned y = 0; y < board_.getSize(); ++y) {
            Color s = Color::RED;
            unsigned counter = 0;
            for (unsigned x = 0; x < board_.getSize(); ++x) {
                if (!board_.isOccupied(x, y)) {
                    s = Color::RED;
                    counter = 0;
                } else if (board_.GetColor(x, y) == s) {
                    counter++;
                } else {
                    counter = 1;
                }
                s = board_.GetColor(x, y);

                if (counter == 5) {
                    return s;
                }
            }
        }
        for (unsigned tx = 0; tx < board_.getSize(); ++tx) {
            Color s = Color::RED;
            unsigned counter = 0;
            unsigned y = 0;
            unsigned x = tx;
            while (x < board_.getSize() && y < board_.getSize()) {
                if (!board_.isOccupied(x, y)) {
                    s = Color::RED;
                    counter = 0;
                } else if (board_.GetColor(x, y) == s) {
                    counter++;
                } else {
                    counter = 1;
                }
                s = board_.GetColor(x, y);

                if (counter == 5) {
                    return s;
                }

                x++;
                y++;
            }
        }
        for (unsigned ty = 0; ty < board_.getSize(); ++ty) {
            Color s = Color::RED;
            unsigned counter = 0;
            unsigned x = 0;
            unsigned y = ty;
            while (x < board_.getSize() && y < board_.getSize()) {
                if (!board_.isOccupied(x, y)) {
                    s = Color::RED;
                    counter = 0;
                } else if (board_.GetColor(x, y) == s) {
                    counter++;
                } else {
                    counter = 1;
                }
                s = board_.GetColor(x, y);

                if (counter == 5) {
                    return s;
                }

                x++;
                y++;
            }
        }

        for (int tx = board_.getSize() - 1; tx >= 0; --tx) {
            Color s = Color::RED;
            unsigned counter = 0;
            unsigned y = 0;
            unsigned x = static_cast<unsigned>(tx);
            while (x < board_.getSize() && y < board_.getSize()) {
                if (!board_.isOccupied(x, y)) {
                    s = Color::RED;
                    counter = 0;
                } else if (board_.GetColor(x, y) == s) {
                    counter++;
                } else {
                    counter = 1;
                }
                s = board_.GetColor(x, y);

                if (counter == 5) {
                    return s;
                }

                x++;
                y--;
            }
        }
        for (int ty = board_.getSize() - 1; ty >= 0; --ty) {
            Color s = Color::RED;
            unsigned counter = 0;
            unsigned x = 0;
            unsigned y = static_cast<unsigned>(ty);
            while (x < board_.getSize() && y < board_.getSize()) {
                if (!board_.isOccupied(x, y)) {
                    s = Color::RED;
                    counter = 0;
                } else if (board_.GetColor(x, y) == s) {
                    counter++;
                } else {
                    counter = 1;
                }
                s = board_.GetColor(x, y);

                if (counter == 5) {
                    return s;
                }

                x++;
                y--;
            }
        }
        return Color::RED;
    }

    std::vector<Coords> GameLogic::prepareTurn(unsigned x, unsigned y, Color) const {
        if (isEnd() != Color::RED) return {};

        if (board_.isOccupied(x, y)) return {};

        return {{x, y}};
    }

    void GameLogic::commitTurn(const std::vector<Coords>& pieces, Color player) {
        for (auto const& fld: pieces) {
            board_.setPiece(fld.GetX(), fld.GetY(), player);
        }
    }


    void GameLogic::setGameBoard(const std::vector<std::string>& GB) {
        for (unsigned i = 0; i < GB.size(); i++) {
            for (unsigned j = 0; j < GB[i].length(); j++) {
                if (GB[i][j] == '0')
                    continue;
                else if (GB[i][j] == '1')
                    board_.setPiece(i, j, Color::BLACK);
                else if (GB[i][j] == '2')
                    board_.setPiece(i, j, Color::WHITE);
                else
                    assert(false);
            }
        }
    }

    std::pair<unsigned, unsigned> GameLogic::getScore() const {

        if (isEnd() == Color::RED)
            return {0, 0};
        else if (isEnd() == Color::BLACK)
            return {1, 0};
        return {0, 1};
    }
}

