//
// Created by ondra on 11.2.16.
//

#include "MainGame.hh"

#include <iostream>


namespace othello {


    void MainGame::initPlayers(){


    }



    void MainGame::event(int x, int y){ // event funkce
    
    }


    
    void MainGame::printGameBoard(){//Zobrazi hraciu plochu na terminal
        for (unsigned i = 0; i < board_.getSize(); i++){
            for (int j = 0; j < board_.getSize(); j++){
                if (board_.isOccupied(i, j))
                    std::cout<<board_.getColor(i,j)<<" ";
                else
                    std::cout<<"_ ";
            }
            std::cout<<std::endl;
        }
    }



}
