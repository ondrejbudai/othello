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
        game = g;
        oldCurrentMove = std::make_pair(x, y);
      }

  void PlayMove::execute(){
        oldBoard = (*game)->getLogic().getBoard().GetBoard();
        oldCurrentPlayer = (*game)->getCurrentPlayerNum();
        (*game)->event(oldCurrentMove.first, oldCurrentMove.second);
        newBoard = (*game)->getLogic().getBoard().GetBoard();
        newCurrentPlayer = (*game)->getCurrentPlayerNum();
      }

      void PlayMove::undo(){
        (*game)->getLogicRef().setGameBoard(oldBoard);
        (*game)->setCurrentPlayer(oldCurrentPlayer);
      }

      void PlayMove::redo(){
        (*game)->getLogicRef().setGameBoard(newBoard);
        (*game)->setCurrentPlayer(newCurrentPlayer);
      }

    void CommandManager::execute(std::shared_ptr<ICommand> command){
      redoStack = commandStack_t();
      command->execute();
      undoStack.push(command);
    }

    void CommandManager::undo(){
      if (undoStack.size() <= 0)
        return;
      undoStack.top()->undo();
      redoStack.push(undoStack.top());
      undoStack.pop();
    }

    void CommandManager::redo(){
      if (redoStack.size() <= 0)
        return;
      redoStack.top()->redo();
      undoStack.push(redoStack.top());
      redoStack.pop();
    }

    void CommandManager::saveAll(std::string fileName){
    }


}
#endif
