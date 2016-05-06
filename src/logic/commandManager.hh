/**
 * @file
 * @brief Manažer undo a redo akcí.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_COMMAND_MANAGER_HH
#define OTHELLO_COMMAND_MANAGER_HH

#include "GameBoard.hh"
#include "MainGame.hh"
#include <stack>
#include <iostream>

namespace othello {

  class ICommand {
    public:
      virtual ~ICommand(){}
      virtual bool Execute() = 0;
      virtual void Undo() = 0;
      virtual void Redo() = 0;
      virtual void SaveToFile(std::ostream &outF) = 0;
  };

  //TODO Uklada aj neplatne tahy!
  //TODO zastavit ked sa zacne babrat, nech AI neblbne
  //TODO ukladanie a nacitanie zo suboru

  class PlayMove: public ICommand{
      std::unique_ptr<MainGame> *game_;
      //std::vector<std::vector<Field>> oldBoard_;
      GameBoard oldBoard_;
      int oldCurrentPlayer_;
      std::pair<unsigned, unsigned> oldCurrentMove_;//nie coords lebo je to class

    public:

      PlayMove(std::unique_ptr<MainGame> *g, unsigned x, unsigned y);
      virtual ~PlayMove(){}
      virtual bool Execute() override;
      virtual void Undo() override;
      virtual void Redo() override;
      virtual void SaveToFile(std::ostream &outF) override;

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

    void SaveToFile(std::ostream &outF);

  };
}

#endif
