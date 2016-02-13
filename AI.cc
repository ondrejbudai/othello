//
// Created by ondra on 11.2.16.
//

#include "AI.hh"
#include "GameLogic.hh"
#include <iostream>

namespace othello {

    //do thisMove ulozi, kam chce tahat
    void AI::play(const GameBoard &board, Coords &thisMove) {
        //Najde vsetky mozne tahy a pre kazdy tah, spocita kolko by zmenil kamenov
        // najdi vsechna volna policka
        std::vector<Coords> emptyFields;
        for (unsigned x = 0; x < board.getSize(); ++x) {
            for (unsigned y = 0; y < board.getSize(); ++y) {
                if (!board.isOccupied(x, y))
                    emptyFields.emplace_back(x, y);
            }
        }

        if (emptyFields.empty()){//toto by sa nemalo stat, skor nez zacne tah, by sme
                                // mali vediet co ozaj moze ist alebo nie
            std::cout<<"SCHEISSE...\n";
            return;
        }
            

        // projdi vsechny, uloz do validMoves "x,y,pocetZmenenychKamenov"
        std::vector<std::pair<Coords,int> > validMoves;
        for (const auto& f : emptyFields) {
            std::vector<Coords> dummy;
            if (isMoveValid(f.GetX(), f.GetY(), Color::WHITE, dummy, board))
                validMoves.push_back(std::make_pair(Coords{f.GetX(), f.GetY()}, dummy.size()));
        }
        
        if (validMoves.empty()){
            std::cout<<"AI nema kam tahat!! COMMON\n";
            return;
        }
        
        //trivialne riesenie ->vyber prve
        Coords tmp{validMoves[0].first.GetX(), validMoves[0].first.GetY()};
        thisMove = tmp;

        //pre kazdy tah, vynasobi si pocet kamenov s konstantou vhodneho umiestenia
        //vrati to, kde ma najvhodnejsie umiestenie
        //trochu sumu do toho?
    }


}//namespace othello
