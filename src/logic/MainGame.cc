/**
* @file
* @brief Správa hry.
* @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
* @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
*/

/*  HLAVICKA
 *  ----------Funkcionalita---------------
 *  Modul sa stara o validitu tahov.
 *  Urcuje ci dany tah je platny a ak je, tak ho necha zapisat.
 *  Zistuje ci exituje tah pre dalsieho hraca, ak ano, tak ho nastavi ako aktualneho hraca.
 *  Implementuje funkciu na zistenie ci exituje aspon jeden platny tah, ak nie jedna sa o koniec hry.
 *  Vramci vykonania tahu zistuje ci je na tahu AI a ak je, tak ho vyzve aby hral. (AJ TAK SA MI TO
 *  NEPACI)
 */

#include "MainGame.hh"
#include "AI.hh"
#include "HardAI.hh"
#include <iostream>
#include <cassert>
#include <memory>

//TODO event vracia bool
//TODO GRaphics scene ma [0,0] v lavom dolnom rohu a rastie smerom hore...

//Sila AI (ako velmi sa snazi vybrat najlepsie riesenie) 0 -> hlada najlepsie riesenie
//                                                       1 -> vybera nahodne riesenie
constexpr double StrengtOfThatBastard = 0;

namespace othello {


    //0 not occupied
    //1 black
    //2 white
    void printBoardToFile(const GameBoard& b, std::ofstream &f){
        for (unsigned i = 0; i < b.GetSize(); ++i){
            for (unsigned j = 0; j < b.GetSize(); ++j){
                Color col;
                bool occupied = b.GetField(i, j).GetStatus(col);
                if (!occupied)
                    f<<0;
                else {
                    if (col == Color::BLACK)
                        f<<1;
                    else
                        f<<2;
                }
            }
            f<<std::endl;
        }
    }



    MainGame::MainGame(unsigned size, PlayerType white, PlayerType black) : logic_{size} {
        //Inicilaizacia hracov
        //TODO je to ozaj najlepsie miesto, nie radsej v OthelloGui a main-cli ?
        std::cout << int(white) << int(black) << "\n";
        if (black == PlayerType::HUMAN){
            players_.push_back(std::make_unique<Player>(Color::BLACK, logic_));
        } else if(black == PlayerType::AI){
            players_.push_back(std::make_unique<AI>(Color::BLACK, logic_, StrengtOfThatBastard ));
        } else
            players_.push_back(std::make_unique<HardAI>(Color::BLACK, logic_, StrengtOfThatBastard ));

        if (white == PlayerType::HUMAN){
            players_.push_back(std::make_unique<Player>(Color::WHITE, logic_));
        } else if(white == PlayerType::AI){
            players_.push_back(std::make_unique<AI>(Color::WHITE, logic_,  StrengtOfThatBastard ));
        } else
            players_.push_back(std::make_unique<HardAI>(Color::WHITE, logic_, StrengtOfThatBastard ));

    }

    Coords MainGame::TellAIToPlay(){
        Player& current_player = *players_[current_player_num_];
        Coords c = current_player.Play();
        return c;

    }


    //Funkcia spracuva zadany tah
    //Na konci tahu, ak je platny, ulozi dany tah do historie
    //Zisti ci je mozne aby dalsi hrac hral, a ak je tak ho nastavuje ako aktualneho hraca
    bool MainGame::Event(unsigned x, unsigned y) { // event funkce

        Player& current_player = *players_[current_player_num_];
        assert(logic_.CanPlay(current_player.GetColor()));


      // priprava tahu
        std::vector<Coords> toChange = logic_.PrepareTurn(x, y, current_player.GetColor());

        //kontrola ci sa jedna o validny tah od uzivatela
        if (toChange.empty()) {
            // aktualni hrac nemuze byt AI (pokud je, AI selhala!)
            assert(!current_player.IsAi());

            //TODO von vypis a vracat false
            std::cout << "Neplatny tah" << std::endl << std::flush;
            return false;
        }

        //zapis tahu
        logic_.CommitTurn(toChange, current_player.GetColor());

        logic_.ClearFlags();

        // zmen hrace, jen pokud ma ten druhy co hrat
        // pokud nema nikdo co hrat, GUI to zjisti
        if(logic_.CanPlay(GetOppositeColor(current_player.GetColor()))){
            current_player_num_++;
            current_player_num_ = current_player_num_ % 2;
        } else if (logic_.CanPlay(current_player.GetColor())){
            //TODO nemoze hrat super, ale mozme hrat my
            //nejaka hlasa na obrazovku
            std::cout<<"Opposite player has no valid moves\n";
        }
        //Zapis nove mozne tahy
        logic_.MarkPossibleMoves((*players_[current_player_num_]).GetColor());
        return true;
    }

     bool MainGame::SaveGameToFile(std::ofstream &outF){
        //TODO HERE
        outF<<players_[0]->GetName()<<std::endl;

        int p = players_[0]->IsAi();
        if ( p == 0)
          outF<<"HUMAN"<<std::endl;
        else if (p == 1)
          outF<<"AI"<<std::endl;
        else
          outF<<"HARDAI"<<std::endl;

        outF<<players_[1]->GetName()<<std::endl;
        p = players_[1]->IsAi();
        if ( p == 0)
          outF<<"HUMAN"<<std::endl;
        else if (p == 1)
          outF<<"AI"<<std::endl;
        else
          outF<<"HARDAI"<<std::endl;

        outF<<logic_.GetBoard().GetSize()<<std::endl;
        return true;
     }



    //Funkcia zistuje ci moze aspon jeden hrac hrat, ak nie jedna sa o koneic hry
    bool MainGame::IsEnd() const {
        return !logic_.CanPlay(Color::BLACK) && !logic_.CanPlay(Color::WHITE);
    }

    //Nastvuje mena hracov
    //TODO rovnako ako v kontruktore, je to na sparvno  mieste?
    void MainGame::SetNames(const std::pair<std::string, std::string>& names) {
        players_[0]->SetName(names.first);
        players_[1]->SetName(names.second);
    }


    std::pair<std::string, std::string> MainGame::GetNames() {
        return std::make_pair(players_[0]->GetName(), players_[1]->GetName());
    }
}
