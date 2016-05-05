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
        if (black == PlayerType::HUMAN)
            players_.push_back(std::make_unique<Player>(Color::BLACK, logic_));
        else
            players_.push_back(std::make_unique<AI>(Color::BLACK, logic_, StrengtOfThatBastard ));

        if (white == PlayerType::HUMAN)
            players_.push_back(std::make_unique<Player>(Color::WHITE, logic_));
        else
            players_.push_back(std::make_unique<AI>(Color::WHITE, logic_,  StrengtOfThatBastard ));

    }

    Coords MainGame::TellAIToPlay(){
        Player& current_player = *players_[current_player_num_];
        assert(CanPlay(current_player.GetColor()));
        assert(current_player.IsAi());

        Coords c = current_player.Play();
        return c;

    }


    //Funkcia spracuva zadany tah
    //Na konci tahu, ak je platny, ulozi dany tah do historie
    //Zisti ci je mozne aby dalsi hrac hral, a ak je tak ho nastavuje ako aktualneho hraca
    bool MainGame::Event(unsigned x, unsigned y) { // event funkce

        Player& current_player = *players_[current_player_num_];
        assert(CanPlay(current_player.GetColor()));


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

        //save game   -aktualny stav + tah co sa ide commitnut + aktualny hrac
        // HistoryItem newH;
        // logic_.copyBoard(newH.board);
        // newH.currentPlayer = current_player.GetColor();
        // newH.currentMove = {x,y};
        // history_.push_back(newH);

        //zapis tahu
        logic_.CommitTurn(toChange, current_player.GetColor());


        // zmen hrace, jen pokud ma ten druhy co hrat
        // pokud nema nikdo co hrat, GUI to zjisti
        if(CanPlay(GetOppositeColor(current_player.GetColor()))){
            current_player_num_++;
            current_player_num_ = current_player_num_ % 2;
        } else if (CanPlay(current_player.GetColor())){
            //TODO nemoze hrat super, ale mozme hrat my
            //nejaka hlasa na obrazovku
            std::cout<<"Opposite player has no valid moves\n";
        }
        return true;
    }

    //Struktura subora s ulozenou hrou
    //
    //BlackPlayerName
    //typ blackPlayera
    //WhitePlayerName
    //typ white player
    //velkost hracej dosky
    //farba kto je na rade [0 alebo 1 podla current player]
    //
    //Hracia doska
    //
    //HISTORY
    //
    //--medzerou oddelene historie, kde kazda ma format
    //farba-kto-zahral x y
    //hracia doska

     bool MainGame::SaveGameToFile(std::ofstream &outF){
        //TODO HERE
        outF<<players_[0]->GetName()<<std::endl;
        outF<<(players_[0]->IsAi() ? "AI":"HUMAN")<<std::endl;
        outF<<players_[1]->GetName()<<std::endl;
        outF<<(players_[1]->IsAi() ? "AI":"HUMAN")<<std::endl;
        outF<<logic_.GetBoard().GetSize()<<std::endl;
        outF<<current_player_num_<<std::endl;
        outF<<std::endl;

        //ziskame akutlanu hraciu dosku
        std::vector<std::vector<Field>> board;
        logic_.GetBoard().Print(outF);

        outF<<"\nHISTORY\n\n";
        return true;
     }



    //Funkcia zistuje ci moze aspon jeden hrac hrat, ak nie jedna sa o koneic hry
    bool MainGame::IsEnd() const {
        return !CanPlay(Color::BLACK) && !CanPlay(Color::WHITE);
    }

    //Urcuje ci moze hrat hrac zadany parametrom
    bool MainGame::CanPlay(Color color) const {
        const GameBoard& board = logic_.GetBoard();

        for (unsigned x = 0; x < board.GetSize(); ++x) {
            for (unsigned y = 0; y < board.GetSize(); ++y) {
                if (!logic_.PrepareTurn(x, y, color).empty())
                    return true;
            }
        }

        return false;
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
