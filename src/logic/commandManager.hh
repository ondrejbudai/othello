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
      virtual void execute() = 0;
      virtual void undo() = 0;
      virtual void redo() = 0;
  };

  //TODO Uklada aj neplatne tahy!
  //TODO zastavit ked sa zacne babrat, nech AI neblbne
  //TODO ukladanie a nacitanie zo suboru

  class PlayMove: public ICommand{
      std::unique_ptr<MainGame> *game;
      std::vector<std::vector<Field>> oldBoard;
      std::vector<std::vector<Field>> newBoard;
      int oldCurrentPlayer;
      int newCurrentPlayer;
      std::pair<unsigned, unsigned> oldCurrentMove;//nie coords lebo je to class

    public:

      PlayMove(std::unique_ptr<MainGame> *g, unsigned x, unsigned y);

      void execute();

      void undo();

      void redo();
  };

  typedef std::stack<std::shared_ptr<ICommand>> commandStack_t;

  class CommandManager{
    commandStack_t undoStack;
    commandStack_t redoStack;

  public:
    CommandManager(){}

    void execute(std::shared_ptr<ICommand> command);

    void undo();

    void redo();

    void saveAll(std::string fileName);

  };
}

#endif
