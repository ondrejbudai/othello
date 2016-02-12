//
// Created by ondra on 11.2.16.
//

#include "MainGame.hh"

#include <iostream>
#include <vector>

namespace othello {


    void MainGame::initPlayers() {


    }


    //Ak uzivatel zada suradnice alebo staci prislusne okenko
    //vracia ukazatel na hraca ktory je na rade
    void MainGame::event(unsigned x, unsigned y) { // event funkce
        std::vector<std::pair<int,int> > toChange;
        if (!isMoveValid(x, y, current_player_, toChange)){
            std::cout<<"Neplatny tah\n";
            return;
        }

        //kontrola ci sa jedna o validny tah od uzivatela co je na rade(ako to kontrolovat?)
        //ak jedna ho nastavime
        board_.setPiece(x, y, current_player_);
        //else ignorujeme (uzivatel moze klikat dobludu a nechceme ho na to upozronovat)
        // ak bol validny zisti ci dalsi hrac ma co hrat
        //ak ma, tak nastav current_player_ na dalsieho inak nemen (Bacha, kontrola ci maju obaja co
        //hrat!)
        //while (current_player == AI){
        //AI.play();//play vyvolava tuto funckiu
        //}
        current_player_ = current_player_ == Color::WHITE ? Color::BLACK : Color::WHITE;

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

    /// x, y su suradnice
    //adding color je farba kamena, ktory chceme pridat
    //toChange je referencia na vektor parov, ktory naplnime vsetkymi poziciami, ktore sa maju
    //zmenit
    bool MainGame::isMoveValid(unsigned x, unsigned y, Color addingColor, std::vector<std::pair<int,int> > &toChange){
        //zistime ci dava na volne policko
        if (board_.isOccupied(x,y))
            return false;//obsadene policko
        std::vector<Field> fields;
        
        //najdeme vsetky susedne policka
        board_.getNeighbours(x, y, fields);
        
        //zo vsetkych susednych vytriedime len tie, ktore su obsadene superom
        std::vector<Field> validFields;
        for (auto const& fld: fields){
            if (fld.occupied_ && fld.piece_ == (addingColor== othello::Color::BLACK ? othello::Color::WHITE : othello::Color::BLACK))
                validFields.push_back(fld);
        }

        //ak sme nic nenasli, invalidny tah
        if (validFields.empty())
            return false;

        //pre kazdy najdeny kamen zistime ci existuje cesta a pridam vsetky kamene z cesty do
        for (auto const& fld: validFields){
            int f = 0;    
        }
        //toChange
        return true;
    }

}
