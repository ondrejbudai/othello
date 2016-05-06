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
#include "CommandManager.hh"

namespace othello {
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
}
#endif
