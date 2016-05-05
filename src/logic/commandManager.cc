//
// Created by matej on 11.2.16.
//

#ifndef OTHELLO_COMMAND_MANAGER_CC
#define OTHELLO_COMMAND_MANAGER_CC

#include "GameBoard.hh"
#include "MainGame.hh"
#include <stack>
#include <iostream>
#include "commandManager.hh"

namespace othello {

  PlayMove::PlayMove(std::unique_ptr<MainGame> *g, unsigned x, unsigned y){
        game_ = g;
        oldCurrentMove_ = std::make_pair(x, y);
      }

  void PlayMove::Execute(){
        oldBoard_ = (*game_)->GetBoard().GetBoard();
        oldCurrentPlayer_ = (*game_)->GetCurrentPlayerNum();
        (*game_)->Event(oldCurrentMove_.first, oldCurrentMove_.second);
        newBoard_ = (*game_)->GetBoard().GetBoard();
        newCurrentPlayer_ = (*game_)->GetCurrentPlayerNum();
      }

      void PlayMove::Undo(){
        (*game_)->GetLogic().SetGameBoard(oldBoard_);
        (*game_)->SetCurrentPlayer(oldCurrentPlayer_);
      }

      void PlayMove::Redo(){
        (*game_)->GetLogic().SetGameBoard(newBoard_);
        (*game_)->SetCurrentPlayer(newCurrentPlayer_);
      }

    void CommandManager::Execute(std::shared_ptr<ICommand> command){
      redoStack_ = commandStack_t();
      command->Execute();
      undoStack_.push(command);
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

    // void CommandManager::SaveAll(std::string fileName){
    // }


}
#endif
