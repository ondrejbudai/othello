//
// Created by ondra on 11.2.16.
//

#include "MainGame.hh"

#include <iostream>
#include <vector>

namespace othello {


    void MainGame::initPlayers(){


    }


    //Ak uzivatel zada suradnice alebo staci prislusne okenko
    //vracia ukazatel na hraca ktory je na rade
    Color MainGame::event(unsigned x, unsigned y, Color playedBy ){ // event funkce
        //kontrola ci sa jedna o validny tah od uzivatela co je na rade(ako to kontrolovat?)
        //ak jedna ho nastavime
        board_.setPiece(x,y, current_player_);
        //else ignorujeme (uzivatel moze klikat dobludu a nechceme ho na to upozronovat)
        // ak bol validny zisti ci dalsi hrac ma co hrat
        //ak ma, tak nastav current_player_ na dalsieho inak nemen (Bacha, kontrola ci maju obaja co
        //hrat!)
        //while (current_player == AI){
            //AI.play();//play vyvolava tuto funckiu
            //} 
        return current_player_;

    }


    //pomocna funkcia pre pracu bez gui 
    void MainGame::printGameBoard(){//Zobrazi hraciu plochu na terminal
        for (unsigned i = 0; i < board_.getSize(); i++){
            for (unsigned j = 0; j < board_.getSize(); j++){
                if (board_.isOccupied(i, j))
                    std::cout<<board_.getColor(i,j)<<" ";
                else
                    std::cout<<"_ ";
            }
            std::cout<<std::endl;
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
            //if (fld.occupied_ && fld.piece_ == addingColor+1)%2)
                validFields.push_back(fld);
        }
        
        //pre kazdy najdeny kamen zistime ci existuje cesta a pridam vsetky kamene z cesty do
        //toChange


    }

}
