//
// Created by ondra on 11.2.16.
//

#include "MainGame.hh"

#include <iostream>
#include <vector>

#define OPOSITE_COLOR(myColor) (myColor == othello::Color::BLACK ? othello::Color::WHITE : othello::Color::BLACK)

namespace othello {


    void MainGame::initPlayers() {


    }


    //Ak uzivatel zada suradnice alebo staci prislusne okenko
    //vracia ukazatel na hraca ktory je na rade
    void MainGame::event(unsigned x, unsigned y) { // event funkce
        std::vector<Field> toChange;
        if (!isMoveValid(x, y, current_player_, toChange)){
            std::cout<<"Neplatny tah\n";
            return;
        }
        for (auto const& fld: toChange){
            board_.setPiece(fld.x_, fld.y_, current_player_);
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
    bool MainGame::isMoveValid(unsigned x, unsigned y, Color addingColor, std::vector<Field> &toChange){
        //zistime ci dava na volne policko
        if (board_.isOccupied(x,y))
            return false;//obsadene policko
        std::vector<Field> fields = board_.getNeighbours(x, y);
        
        //zo vsetkych susednych vytriedime len tie, ktore su obsadene superom
        std::vector<Field> oppositeFields;
        for (auto const& fld: fields){
            if (fld.occupied_ && fld.piece_ == OPOSITE_COLOR(addingColor))
                oppositeFields.push_back(fld);
        }

        //ak sme nic nenasli, invalidny tah
        if (oppositeFields.empty())
            return false;

        //pre kazdy najdeny kamen zistime ci existuje cesta a pridam vsetky kamene z cesty do
        for (auto const& fld: oppositeFields){
            int deltaX = fld.x_ - x; //smer posuvania x
            int deltaY = fld.y_ - y; //smer posuvania y
            int pomX = x; 
            int pomY = y;
            std::vector<Field> possibleChanges;
            while (true){
                pomX += deltaX;
                pomY += deltaY;
                //ak sme sa dostali mimo pole
                if (pomX < 0 || pomX >= int(board_.getSize()) || pomY < 0 || pomY >= int(board_.getSize()))
                    break;
                Field candidat = board_.GetField(pomX, pomY);
                //ak dane poliecko nie je obsadene, nie je to kandidat
                if (!candidat.occupied_)
                    break;
                //ak sme nasli svoju farbu a mame aspon jednu superovu medzitym
                if (candidat.piece_ == addingColor && !possibleChanges.empty()){
                    for (unsigned f = 0; f < possibleChanges.size(); f++)
                        std::cout<<possibleChanges[f].x_<<" "<<possibleChanges[f].y_<<std::endl<<std::flush;
                    toChange.insert(toChange.end(), possibleChanges.begin(), possibleChanges.end());
                    std::cout<<"Najdeny jeden vektor\n";
                    break;
                }
                //ak patri field superovy
                if (candidat.piece_ == OPOSITE_COLOR(addingColor))  
                    possibleChanges.push_back(candidat);
            }

        }
        if (toChange.empty())
            return false;

        return true;
    }

}
