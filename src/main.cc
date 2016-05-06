/**
* @file
* @brief Spouštěcí soubor pro terminálovou verzi.
* @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
* @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
*/

#include "logic/MainGame.hh"
#include <iostream>
#include "logic/CommandManager.hh"
#include <memory>

int main() {
    //vytvorime obrazovky
    //so vsetkym klikanim a pod
    //ak si vyberie novu hru a klikne start, tak sa zavola funkcia othello::MainGame(parametre)
    std::unique_ptr<othello::MainGame> g = std::make_unique<othello::MainGame>(8, othello::PlayerType::HUMAN, othello::PlayerType::AI);
    //othello::MainGame g(8, othello::PlayerType::HUMAN, othello::PlayerType::AI);//toto potom tu nebude
    othello::CommandManager cmd_ = othello::CommandManager();
    //samotne okno pri udalosti, vyvola funkcie, ktore su implementovane v gamelogic a v maingame
    //nasledujuca cast je pre terminal a tesotvanie
    while (!g->IsEnd()) {
        g->GetBoard().Print(std::cout);
        std::cout << "Na tahu je " << (g->GetCurrentPlayer().GetColor() == othello::Color::BLACK ? "BLACK" : "WHITE") <<
        std::endl;

        // zjisti souradnice (pokud nehraje AI)
        int x = 0, y = 0;
        if (!g->GetCurrentPlayer().IsAi()) {
            std::cout << "Zadaj suradnice: " << std::flush;
            std::cin >> x >> y;
        }

        //g.event(x, y);
        std::shared_ptr<othello::ICommand> c(new othello::PlayMove(&g, x, y));
        cmd_.Execute(c);
    }
}
