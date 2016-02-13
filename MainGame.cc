//
// Created by ondra on 11.2.16.
//

#include "MainGame.hh"

#include <iostream>
#include <vector>

namespace othello {

    inline Color GetOppositeColor(Color myColor) {
        return myColor == othello::Color::BLACK ? othello::Color::WHITE : othello::Color::BLACK;
    }

    void MainGame::initPlayers() {


    }


    //Ak uzivatel zada suradnice alebo staci prislusne okenko
    //vracia ukazatel na hraca ktory je na rade
    void MainGame::event(unsigned x, unsigned y) { // event funkce
        //kontrola ci sa jedna o validny tah od uzivatela
        std::vector<Coords> toChange;
        if (!isMoveValid(x, y, current_player_, toChange)) {
            std::cout << "Neplatny tah\n"<<std::flush;
            return;
        }
        for (auto const& fld: toChange) {
            board_.setPiece(fld.first, fld.second, current_player_);
        }

        //ak jedna ho nastavime
        board_.setPiece(x, y, current_player_);

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
    bool MainGame::isMoveValid(unsigned x, unsigned y, Color addingColor, std::vector<Coords>& toChange) {

        Color oppositeColor = GetOppositeColor(addingColor);

        //zistime ci dava na volne policko
        if (board_.isOccupied(x, y))
            return false;//obsadene policko
        std::vector<Coords> fields = board_.getNeighbours(x, y);

        //zo vsetkych susednych vytriedime len tie, ktore su obsadene superom
        std::vector<Coords> oppositeFields;
        for (auto const& fld: fields) {
            if (board_.isOccupied(fld) && board_.GetColor(fld) == oppositeColor)
                oppositeFields.push_back(fld);
        }

        //ak sme nic nenasli, invalidny tah
        if (oppositeFields.empty())
            return false;

        //pre kazdy najdeny kamen zistime ci existuje cesta a pridam vsetky kamene z cesty do
        for (auto const& fld: oppositeFields) {
            int deltaX = fld.first - x; //smer posuvania x
            int deltaY = fld.second - y; //smer posuvania y
            int pomX = x;
            int pomY = y;
            std::vector<Coords> possibleChanges;
            while (true) {
                pomX += deltaX;
                pomY += deltaY;
                //ak sme sa dostali mimo pole
                if (pomX < 0 || pomX >= int(board_.getSize()) || pomY < 0 || pomY >= int(board_.getSize()))
                    break;
                Coords candidate{pomX, pomY};
//                Field candidate = board_.GetField(pomX, pomY);
                //ak dane poliecko nie je obsadene, nie je to kandidat
                if (!board_.isOccupied(candidate))
                    break;
                //ak sme nasli svoju farbu a mame aspon jednu superovu medzitym
                if (board_.GetColor(candidate) == addingColor && !possibleChanges.empty()) {
                    toChange.insert(end(toChange), begin(possibleChanges), end(possibleChanges));
                    break;
                }
                //ak sme nasli nas kamen, ale nic medzi nim
                if (board_.GetColor(candidate) == addingColor && possibleChanges.empty())
                    break;       
                //ak patri field superovy
                if (board_.GetColor(candidate) == oppositeColor)
                    possibleChanges.push_back(candidate);
            }

        }
        //DUPLICITY v toChange
        if (toChange.empty())
            return false;

        return true;
    }

    bool MainGame::isEnd() {

        // najdi vsechna volna policka
        std::vector<Coords> emptyFields;
        for (unsigned x = 0; x < board_.getSize(); ++x) {
            for (unsigned y = 0; y < board_.getSize(); ++y) {
                if (!board_.isOccupied(x, y))
                    emptyFields.emplace_back(x, y);
            }
        }

        if (emptyFields.empty())
            return true;

        // projdi vsechny, pokud je alespon pro jednoho hrace mozny tah, hra nekonci
        std::vector<Coords> dummy;
        for (const auto& f : emptyFields) {
            if (isMoveValid(f.first, f.second, Color::WHITE, dummy) ||
                isMoveValid(f.first, f.second, Color::BLACK, dummy))
                return false;
        }

        return true;
    }
}
