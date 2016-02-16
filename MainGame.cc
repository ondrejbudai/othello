//
// Created by ondra on 11.2.16.
//

#include "MainGame.hh"

#include <iostream>
#include <cassert>

namespace othello {
    MainGame::MainGame(unsigned size, PlayerType white, PlayerType black) : logic_{size} {
        if (white == PlayerType::HUMAN)
            players_.push_back(std::make_unique<Player>(Color::WHITE, logic_));
        else
            players_.push_back(std::make_unique<AI>(Color::WHITE, logic_, 0));
        if (black == PlayerType::HUMAN)
            players_.push_back(std::make_unique<Player>(Color::BLACK, logic_));
        else
            players_.push_back(std::make_unique<AI>(Color::BLACK, logic_, 0));
    
        

    }


    //Ak uzivatel zada suradnice alebo staci prislusne okenko
    //vracia ukazatel na hraca ktory je na rade
    void MainGame::event(unsigned x, unsigned y) { // event funkce
        if (!IsRunning())
            return;
         
        Player& current_player = *players_[current_player_num];

        assert(canPlay(current_player.getColor()));

        // pokud je aktualne na tahu AI, ziskame tah
        if(current_player.isAi()){
            Coords c = current_player.play();
            x = c.GetX();
            y = c.GetY();
        }

        // priprava tahu
        std::vector<Coords> toChange = logic_.prepareTurn(x, y, current_player.getColor());

        //kontrola ci sa jedna o validny tah od uzivatela
        if (toChange.empty()) {
            // aktualni hrac nemuze byt AI (pokud je, AI selhala!)
            assert(!current_player.isAi());

            std::cout << "Neplatny tah" << std::endl << std::flush;
            return;
        }

        logic_.commitTurn(toChange, current_player.getColor());

        
        //zavolame aj v GUI ukazovanie skore
        
        
        // zmen hrace, jen pokud ma ten druhy co hrat
        // pokud nema nikdo co hrat, GUI to zjisti
        if(canPlay(GetOppositeColor(current_player.getColor()))){
            current_player_num++;
            current_player_num = current_player_num % 2;
        }
    }


    //pomocna funkcia pre pracu bez gui
    //TODO: move me!
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
        return !canPlay(Color::BLACK) && !canPlay(Color::WHITE);
    }

    bool MainGame::canPlay(Color color) const {
        const GameBoard& board = logic_.getBoard();

        for (unsigned x = 0; x < board.getSize(); ++x) {
            for (unsigned y = 0; y < board.getSize(); ++y) {
                if (!logic_.prepareTurn(x, y, color).empty())
                    return true;
            }
        }

        return false;
    }
}
