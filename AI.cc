//
// Created by ondra on 11.2.16.
//

#include "AI.hh"
#include <iostream>
#include <map>

namespace othello {

    //do thisMove ulozi, kam chce tahat
    Coords AI::play() {
        //Najde vsetky mozne tahy a pre kazdy tah, spocita kolko by zmenil kamenov
        // najdi vsechna volna policka
        std::vector<Coords> emptyFields;
        const GameBoard& board = logic_.getBoard();

        for (unsigned x = 0; x < board.getSize(); ++x) {
            for (unsigned y = 0; y < board.getSize(); ++y) {
                if (!board.isOccupied(x, y))
                    emptyFields.emplace_back(x, y);
            }
        }

        if (emptyFields.empty()){//toto by sa nemalo stat, skor nez zacne tah, by sme
                                // mali vediet co ozaj moze ist alebo nie
            std::cout<<"SCHEISSE...\n";
            //vyjimka?
        }


        // projdi vsechny, uloz do validMoves s indexem pocet upravenych kamenu
        std::map<unsigned, Coords> validMoves;
        for (const auto& f : emptyFields) {
            unsigned changedPieces = logic_.prepareTurn(f.GetX(), f.GetY(), color_).size();
            if (changedPieces > 0)
                validMoves.insert({changedPieces, f});
        }
        
        if (validMoves.empty()){
            std::cout<<"AI nema kam tahat!! COMMON\n";
            //vyjimka?
        }

        // map je serazena, vezmeme posledni prvek (na ktery ukazuje reverzni iterator)
        return validMoves.rbegin()->second;

        //pre kazdy tah, vynasobi si pocet kamenov s konstantou vhodneho umiestenia
        //vrati to, kde ma najvhodnejsie umiestenie
        //trochu sumu do toho?
    }


}//namespace othello
