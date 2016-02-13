//
// Created by ondra on 11.2.16.
//

#include "MainGame.hh"

#include <iostream>

namespace othello {
    MainGame::MainGame(unsigned size, PlayerType white, PlayerType black) : logic_{size} {
        if (white == PlayerType::HUMAN)
            players_.push_back(std::make_unique<Player>(Color::WHITE, logic_));
        else
            players_.push_back(std::make_unique<AI>(Color::WHITE, logic_));
        if (black == PlayerType::HUMAN)
            players_.push_back(std::make_unique<Player>(Color::BLACK, logic_));
        else
            players_.push_back(std::make_unique<AI>(Color::BLACK, logic_));
    }


    //Ak uzivatel zada suradnice alebo staci prislusne okenko
    //vracia ukazatel na hraca ktory je na rade
    void MainGame::event(unsigned x, unsigned y) { // event funkce
        Color current_player_ = players_[current_player_num]->getColor();
        //kontrola ci sa jedna o validny tah od uzivatela
        std::vector<Coords> toChange = logic_.prepareTurn(x, y, current_player_);
        if (toChange.empty()) {
            std::cout << "Neplatny tah\n" << std::flush;
            return;
        }

        logic_.commitTurn(toChange, current_player_);

        // ak bol validny zisti ci dalsi hrac ma co hrat
        //ak ma, tak nastav current_player_ na dalsieho inak nemen (Bacha, kontrola ci maju obaja co
        //hrat!)
        //while (current_player == AI){
        //AI.play();//play vyvolava tuto funckiu
        //}
        current_player_num++;
        current_player_num = current_player_num % 2;

        //TODO: Tohle zpusobuje fakt hnusnou rekurzi, pokud hraji pouze AI!
        if (players_[current_player_num]->isAi()) {
            Coords thisMove = players_[current_player_num]->play();
            std::cout << "AI zahral: " << thisMove.GetX() << " " << thisMove.GetY() << std::endl << std::flush;
            this->event(thisMove.GetX(), thisMove.GetY());
        }
        //current_player_ = current_player_ == Color::WHITE ? Color::BLACK : Color::WHITE;

    }


    //pomocna funkcia pre pracu bez gui 
    void MainGame::printGameBoard() const {//Zobrazi hraciu plochu na terminal
        using namespace std;

        const GameBoard& board = logic_.getBoard();

        cout << "   ";
        for (unsigned i = 0; i < board.getSize(); i++) {
            cout << i;
            if (i < 10)
                cout << " ";
        }
        cout << endl;
        for (unsigned i = 0; i < board.getSize(); i++) {
            if (i < 10)
                cout << " ";
            cout << i << " ";
            for (unsigned j = 0; j < board.getSize(); j++) {
                if (board.isOccupied(i, j))
                    cout << (board.GetField(i, j).piece_ == Color::BLACK ? "\u25CB" : "\u25CD") << " ";
                else
                    cout << "  ";
            }
            cout << endl;
        }
    }

    bool MainGame::isEnd() const {
        const GameBoard& board = logic_.getBoard();

        for (unsigned x = 0; x < board.getSize(); ++x) {
            for (unsigned y = 0; y < board.getSize(); ++y) {
                if (!logic_.prepareTurn(x, y, Color::WHITE).empty() ||
                    !logic_.prepareTurn(x, y, Color::BLACK).empty())
                    return false;
            }
        }

        return true;
    }
}
