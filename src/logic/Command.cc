/**
 * @file
 * @brief Jeden vrátiteľný príkaz.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_COMMAND_MANAGER_CC
#define OTHELLO_COMMAND_MANAGER_CC

#include "GameBoard.hh"
#include "MainGame.hh"
#include <stack>
#include <iostream>
#include "Command.hh"

namespace othello {

  PlayMove::PlayMove(std::unique_ptr<MainGame> *g, unsigned x, unsigned y)
    :oldBoard_((*g)->GetBoard())
  {
        game_ = g;
        oldCurrentMove_ = std::make_pair(x, y);
      }

  bool PlayMove::Execute(){
        oldCurrentPlayer_ = (*game_)->GetCurrentPlayerNum();
        if (!(*game_)->Event(oldCurrentMove_.first, oldCurrentMove_.second))
          return false;
        return true;
      }

      void PlayMove::Undo(){
        (*game_)->GetLogic().SetGameBoard(oldBoard_);
        (*game_)->SetCurrentPlayer(oldCurrentPlayer_);
      }

      void PlayMove::Redo(){
        (*game_)->Event(oldCurrentMove_.first, oldCurrentMove_.second);
      }

    void PlayMove::SaveToFile(std::ostream &outF){
            outF<<oldCurrentMove_.first<<" "<<oldCurrentMove_.second<<std::endl;
    }
}
#endif
