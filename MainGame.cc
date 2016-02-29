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

//TODO event vracia bool

//Sila AI (ako velmi sa snazi vybrat najlepsie riesenie) 0 -> hlada najlepsie riesenie
//                                                       1 -> vybera nahodne riesenie
constexpr double StrengtOfThatBastard = 0;


namespace othello {

    MainGame::MainGame(unsigned size, PlayerType white, PlayerType black) : logic_{size} {
        //Inicilaizacia hracov
        //TODO je to ozaj najlepsie miesto, nie radsej v OthelloGui a main-cli ?
        if (white == PlayerType::HUMAN)
            players_.push_back(std::make_unique<Player>(Color::WHITE, logic_));
        else
            players_.push_back(std::make_unique<AI>(Color::WHITE, logic_,  StrengtOfThatBastard ));
        
        if (black == PlayerType::HUMAN)
            players_.push_back(std::make_unique<Player>(Color::BLACK, logic_));
        else
            players_.push_back(std::make_unique<AI>(Color::BLACK, logic_, StrengtOfThatBastard ));
    }


    //Funkcia spracuva zadany tah
    //Na konci tahu, ak je platny, ulozi dany tah do historie
    //Zisti ci je mozne aby dalsi hrac hral, a ak je tak ho nastavuje ako aktualneho hraca
    void MainGame::event(unsigned x, unsigned y) { // event funkce
        //koniec hry
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

            //TODO von vypis a vracat false
            std::cout << "Neplatny tah" << std::endl << std::flush;
            return;
        }
        
        //TODO save game   -aktualny stav + tah co sa ide commitnut + akrualny hrac

        //zapis tahu
        logic_.commitTurn(toChange, current_player.getColor());
        
        
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

    //Funkcia zistuje ci moze aspon jeden hrac hrat, ak nie jedna sa o koneic hry
    bool MainGame::isEnd() const {
        return !canPlay(Color::BLACK) && !canPlay(Color::WHITE);
    }

    //Urcuje ci moze hrat hrac zadany parametrom
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

    //Nastvuje mena hracov
    //TODO rovnako ako v kontruktore, je to na sparvno  mieste?
    void MainGame::setNames(const std::vector<std::string>& names) {
        players_[0]->setName(names[0]);
        players_[1]->setName(names[1]);
    }
}
