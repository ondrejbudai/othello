//
// Created by ondra on 11.2.16.
//

#include "MainGame.hh"
#include "GameBoard.hh"
#include <iostream>

int main() {
    //vytvorime obrazovky
    //so vsetkym klikanim a pod
    //ak si vyberie novu hru a klikne start, tak sa zavola funkcia othello::MainGame(parametre)
    othello::MainGame g(8);//toto potom tu nebude
    //samotne okno pri udalosti, vyvola funkcie, ktore su implementovane v gamelogic a v maingame
    //nasledujuca cast je pre terminal a tesotvanie
    while (true) {
        g.printGameBoard();
        std::cout << "Na tahu je " << (g.getCurrentPlayer() == othello::Color::BLACK ? "BLACK" : "WHITE") << std::endl;
        std::cout << "Zadaj suradnice: " << std::flush;
        int x, y;
        std::cin >> x >> y;
        g.event(x, y);//but vrati tu istu farbu ak je druhy AI, alebo vrati opacnu  farbu
        // ak ma tah...
        if (g.isEnd())
            break;
    }
}
