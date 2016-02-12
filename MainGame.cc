//
// Created by ondra on 11.2.16.
//

#include "MainGame.hh"

#include <iostream>


namespace othello {


    void MainGame::initPlayers(){


    }


    //Ak uzivatel zada suradnice alebo staci prislusne okenko
    //vracia ukazatel na hraca ktory je na rade
    Color MainGame::event(unsigned x, unsigned y ){ // event funkce
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



}
