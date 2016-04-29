//
// Created by ondra on 11.2.16.
//

#include "logic/MainGame.hh"
#include <iostream>

int main() {
    //vytvorime obrazovky
    //so vsetkym klikanim a pod
    //ak si vyberie novu hru a klikne start, tak sa zavola funkcia othello::MainGame(parametre)
    othello::MainGame g(8, othello::PlayerType::HUMAN, othello::PlayerType::AI);//toto potom tu nebude
    //samotne okno pri udalosti, vyvola funkcie, ktore su implementovane v gamelogic a v maingame
    //nasledujuca cast je pre terminal a tesotvanie
    while (!g.isEnd()) {
        g.printGameBoard();
        std::cout << "Na tahu je " << (g.getCurrentPlayer().getColor() == othello::Color::BLACK ? "BLACK" : "WHITE") <<
        std::endl;

        // zjisti souradnice (pokud nehraje AI)
        int x = 0, y = 0;
        if (!g.getCurrentPlayer().isAi()) {
            std::cout << "Zadaj suradnice: " << std::flush;
            std::cin >> x >> y;
        }

        g.event(x, y);
    }
}
