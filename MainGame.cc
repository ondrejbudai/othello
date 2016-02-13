//
// Created by ondra on 11.2.16.
//

#include "MainGame.hh"
#include "GameLogic.hh"

#include <iostream>
#include <vector>

namespace othello {
    MainGame::MainGame(unsigned size) : board_{size} {
        players_[0] = new Player(Color::WHITE);//priklad
        players_[1] = new AI(Color::BLACK);//priklad
    }



    //Ak uzivatel zada suradnice alebo staci prislusne okenko
    //vracia ukazatel na hraca ktory je na rade
    void MainGame::event(unsigned x, unsigned y) { // event funkce
        Color current_player_ = players_[current_player_num]->getColor();
        //kontrola ci sa jedna o validny tah od uzivatela
        std::vector<Coords> toChange;
        if (!isMoveValid(x, y, current_player_, toChange, board_)) {
            std::cout << "Neplatny tah\n"<<std::flush;
            return;
        }
        for (auto const& fld: toChange) {
            board_.setPiece(fld.first, fld.second, current_player_);
        }

        //ak jedna ho nastavime
        board_.setPiece(x, y, current_player_);
        
        // ak bol validny zisti ci dalsi hrac ma co hrat
        //ak ma, tak nastav current_player_ na dalsieho inak nemen (Bacha, kontrola ci maju obaja co
        //hrat!)
        //while (current_player == AI){
        //AI.play();//play vyvolava tuto funckiu
        //}
        current_player_num++;
        current_player_num = current_player_num % 2;
        if (players_[current_player_num]->isAi()){
            Coords thisMove;
            players_[current_player_num]->play(board_,thisMove);
            std::cout<<"AI zahral: "<<thisMove.first<<" "<<thisMove.second<<std::endl<<std::flush;
            this->event(thisMove.first, thisMove.second);
        }
        //current_player_ = current_player_ == Color::WHITE ? Color::BLACK : Color::WHITE;

    }


    //pomocna funkcia pre pracu bez gui 
    void MainGame::printGameBoard() const {//Zobrazi hraciu plochu na terminal
        using namespace std;
        cout << "   ";
        for (unsigned i = 0; i < board_.getSize(); i++) {
            cout << i;
            if (i < 10)
                cout << " ";
        }
        cout << endl;
        for (unsigned i = 0; i < board_.getSize(); i++) {
            if (i < 10)
                cout << " ";
            cout << i << " ";
            for (unsigned j = 0; j < board_.getSize(); j++) {
                if (board_.isOccupied(i, j))
                    cout << (board_.GetField(i, j).piece_ == Color::BLACK ? "\u25CB" : "\u25CD") << " ";
                else
                    cout << "  ";
            }
            cout << endl;
        }
    }


}
