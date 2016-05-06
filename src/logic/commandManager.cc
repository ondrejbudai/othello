/**
 * @file
 * @brief Manažer undo a redo akcí.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_COMMAND_MANAGER_CC
#define OTHELLO_COMMAND_MANAGER_CC

#include "GameBoard.hh"
#include "MainGame.hh"
#include <stack>
#include <iostream>
#include "commandManager.hh"

namespace othello {

  PlayMove::PlayMove(std::unique_ptr<MainGame> *g, unsigned x, unsigned y)
    :oldBoard_((*g)->GetBoard())
  {
        game_ = g;
        oldCurrentMove_ = std::make_pair(x, y);
      }

  bool PlayMove::Execute(){
        //oldBoard_ = (*game_)->GetBoard().GetBoard();
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
        //(*game_)->GetLogic().SetGameBoard(newBoard_);
        //(*game_)->SetCurrentPlayer(newCurrentPlayer_);
      }

    void CommandManager::Execute(std::shared_ptr<ICommand> command){
      if (command->Execute()){
        redoStack_ = commandStack_t();
        undoStack_.push(command);
      }
    }

    void CommandManager::Undo(){
      if (undoStack_.size() <= 0)
        return;
      undoStack_.top()->Undo();
      redoStack_.push(undoStack_.top());
      undoStack_.pop();
    }

    void CommandManager::Redo(){
      if (redoStack_.size() <= 0)
        return;
      redoStack_.top()->Redo();
      undoStack_.push(redoStack_.top());
      redoStack_.pop();
    }

    void CommandManager::SaveToFile(std::ostream &outF){
        while (undoStack_.size() > 0){
          redoStack_.push(undoStack_.top());
          undoStack_.pop();
        }
        outF<<redoStack_.size()<<std::endl;
        while (redoStack_.size() > 0){
          redoStack_.top()->SaveToFile(outF);
          undoStack_.push(redoStack_.top());
          redoStack_.pop();
        }
    }

    void PlayMove::SaveToFile(std::ostream &outF){
            //oldBoard_.Print(outF);
            //outF<<std::endl<<oldCurrentPlayer_<<std::endl;
            outF<<oldCurrentMove_.first<<" "<<oldCurrentMove_.second<<std::endl;
    }
}
#endif
