/**
 * @file
 * @brief Manažer undo a redo akcí.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_COMMAND_MANAGER_HH
#define OTHELLO_COMMAND_MANAGER_HH

//#include "GameBoard.hh"
//#include "MainGame.hh"
#include <stack>
#include <iostream>
#include "Command.hh"

namespace othello {
  /**
   * @brief Zásobník príkazov.
   * @typedef commandStack_t
   */
  typedef std::stack<std::shared_ptr<ICommand>> commandStack_t;

  /**
   * @brief Ulož príkazy a prepínaj medzi nimi.
   * @class CommandManager
   */
  class CommandManager{
    /**
     * @brief Zásobník príkazov, ktoré je možné vrátiť späť.
     * @var undoStack_
     */
    commandStack_t undoStack_;

    /**
     * @brief Zásobník stavov, s ktorými je možné urobiť krok vpred.
     * @var redoStack_
     */
    commandStack_t redoStack_;

  public:
    /**
     * @brief Konštruktor CommandManager.
     * @method CommandManager
     */
    CommandManager(){}

    /**
     * @brief Vykonaj a ulož príkaz predaný parametrom
     * @method Execute
     * @param  command príkaz, ktorý má byť vykonaný a uložený.
     */
    void Execute(std::shared_ptr<ICommand> command);

    /**
     * @brief Vrať jeden príkaz späť.
     * @method Undo
     */
    void Undo();

    /**
     * @brief O jeden príkaz krok vpred.
     * @method Redo
     */
    void Redo();

    /**
     * @brief Ulož všetky príkazy do súboru.
     * @method SaveToFile
     * @param  outF       otvorený popisovač súboru.
     */
    void SaveToFile(std::ostream &outF);

  };
}

#endif
