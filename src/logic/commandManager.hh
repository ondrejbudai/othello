//
// Created by matej on 11.2.16.
//

#ifndef OTHELLO_COMMAND_MANAGER_HH
#define OTHELLO_COMMAND_MANAGER_HH

#include "GameBoard.hh"
#include "MainGame.hh"
#include <stack>
#include <iostream>

namespace othello {

  class ICommand {
    public:
      virtual bool Execute() = 0;
      virtual void Undo() = 0;
      virtual void Redo() = 0;
  };

  //TODO Uklada aj neplatne tahy!
  //TODO zastavit ked sa zacne babrat, nech AI neblbne
  //TODO ukladanie a nacitanie zo suboru

  class PlayMove: public ICommand{
      std::unique_ptr<MainGame> *game_;
      std::vector<std::vector<Field>> oldBoard_;
      int oldCurrentPlayer_;
      std::pair<unsigned, unsigned> oldCurrentMove_;//nie coords lebo je to class

    public:

      PlayMove(std::unique_ptr<MainGame> *g, unsigned x, unsigned y);

      bool Execute() override;

      void Undo() override;

      void Redo() override;

  };

  typedef std::stack<std::shared_ptr<ICommand>> commandStack_t;

  class CommandManager{
    commandStack_t undoStack_;
    commandStack_t redoStack_;

  public:
    CommandManager(){}

    void Execute(std::shared_ptr<ICommand> command);

    void Undo();

    void Redo();

    void SaveAllToFile(std::ostream &outF);

  };
}

#endif
