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
//TODO GRaphics scene ma [0,0] v lavom dolnom rohu a rastie smerom hore...

//Sila AI (ako velmi sa snazi vybrat najlepsie riesenie) 0 -> hlada najlepsie riesenie
//                                                       1 -> vybera nahodne riesenie
constexpr double StrengtOfThatBastard = 0;


namespace othello {
    
    //0 not occupied
    //1 black
    //2 white
    void printBoardToFile(std::vector<std::vector<Field>> b, std::ofstream &f){
        for (unsigned i = 0; i < b.size(); ++i){
            for (unsigned j = 0; j < b.size(); ++j){
                if (!b[i][j].occupied_)
                    f<<0;
                else {
                    if (b[i][j].piece_ == Color::BLACK)
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


    //Funkcia spracuva zadany tah
    //Na konci tahu, ak je platny, ulozi dany tah do historie
    //Zisti ci je mozne aby dalsi hrac hral, a ak je tak ho nastavuje ako aktualneho hraca
    void MainGame::event(unsigned x, unsigned y) { // event funkce

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
        
        //save game   -aktualny stav + tah co sa ide commitnut + aktualny hrac
        HistoryItem newH;
        logic_.copyBoard(newH.board);
        newH.currentPlayer = current_player.getColor();
        newH.currentMove = {x,y};
        history_.push_back(newH);

        //zapis tahu
        logic_.commitTurn(toChange, current_player.getColor());
        
        
        // zmen hrace, jen pokud ma ten druhy co hrat
        // pokud nema nikdo co hrat, GUI to zjisti
        if(canPlay(GetOppositeColor(current_player.getColor()))){
            current_player_num++;
            current_player_num = current_player_num % 2;
        } else if (canPlay(current_player.getColor())){
            //TODO nemoze hrat super, ale mozme hrat my
            //nejaka hlasa na obrazovku
            std::cout<<"Opposite player has no valid moves\n";
        }

        //printHistory();
        //printGameBoard();
        


    }

    void MainGame::addToHistory(HistoryItem n){
        history_.push_back(n);
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

    //pomocna funkcia pre pracu bez gui vypis historie
    //TODO: move me!
    void MainGame::printHistory() const {
        using namespace std;

        //TODO PREpocitat pozicie

        cout<<"-------------OTHELLOS STORY-----------------------";
            for (unsigned k = 0; k < history_.size(); k++){
                cout<<endl;
                cout<< "Na rade je "<<(history_[k].currentPlayer == Color::BLACK ? "black":"white")<<" a zahra "<<history_[k].currentMove.first<<" "<<history_[k].currentMove.first<<endl;
                cout<<endl;

                unsigned sz = history_[k].board.size();

                cout << "   ";
                for (unsigned i = 0; i < sz; i++) {
                    cout << i;
                    if (i < 10)
                        cout << " ";
                }
                cout << endl;
                for (unsigned i = 0; i < sz; i++) {
                    if (i < 10)
                        cout << " ";
                    cout << i << " ";
                    for (unsigned j = 0; j < sz; j++) {
                        if (history_[k].board[i][j].occupied_)
                            cout << (history_[k].board[i][j].piece_ == Color::BLACK ? "\u25CB" : "\u25CD") << " ";
                        else
                            cout << "  ";
                    }
                    cout << endl;
                }
            }        
        cout<<"-------------OTHELLOS STORY ENDS------------------";
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
    bool MainGame::saveGameToFile(std::ofstream &outF){
        //TODO HERE
        outF<<players_[0]->getName()<<std::endl;
        outF<<(players_[0]->isAi() ? "AI":"HUMAN")<<std::endl;
        outF<<players_[1]->getName()<<std::endl;
        outF<<(players_[1]->isAi() ? "AI":"HUMAN")<<std::endl;
        outF<<logic_.getBoard().getSize()<<std::endl;
        outF<<current_player_num<<std::endl;
        outF<<std::endl;
       
        //ziskame akutlanu hraciu dosku 
        std::vector<std::vector<Field>> board;
        logic_.copyBoard(board);
        
        printBoardToFile(board, outF);
        
        outF<<"\nHISTORY\n\n";

        for (auto const& hisItem:history_){
            outF<<(hisItem.currentPlayer == Color::BLACK?"black":"white")<<std::endl;
            outF<<hisItem.currentMove.first<<std::endl;
            outF<<hisItem.currentMove.second<<std::endl;
            printBoardToFile(hisItem.board, outF);
        }
        return true;
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
    void MainGame::SetNames(const std::pair<std::string, std::string>& names) {
        players_[0]->setName(names.first);
        players_[1]->setName(names.second);
    }


    std::pair<std::string, std::string> MainGame::GetNames() {
        return std::make_pair(players_[0]->getName(), players_[1]->getName());
    }
}
