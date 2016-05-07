/**
 * @file
 * @brief Jeden vrátiteľný príkaz.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_COMMAND_HH
#define OTHELLO_COMMAND_HH

#include "GameBoard.hh"
#include "MainGame.hh"
#include <stack>
#include <iostream>

namespace othello {

  /**
   * @brief Jeden uskutočniteľný príkaz.
   * @class ICommand
   */
  class ICommand {
    public:
      /**
       * @brief Deštruktor príkazu.
       * @method ~ICommand
       */
      virtual ~ICommand(){}

      /**
       * @brief Vykonaj príkaz.
       * @method Execute
       * @return True ak vykonaný úspešne.
       */
      virtual bool Execute() = 0;

      /**
       * @brief Krok späť.
       * @method Undo
       */
      virtual void Undo() = 0;

      /**
       * @brief Krok vpred.
       * @method Redo
       */
      virtual void Redo() = 0;

      /**
       * @brief Ulož príkaz do súboru.
       * @method SaveToFile
       * @param  outF       otvorený popisovač súboru.
       */
      virtual void SaveToFile(std::ostream &outF) = 0;
  };

  /**
   * @brief Príkaz na zahranie ťahu.
   * @class PlayMove
   */
  class PlayMove: public ICommand{
      /**
       * @brief Referencia na aktuálnu hru.
       * @var game_
       */
      std::unique_ptr<MainGame> *game_;

      /**
       * @brief Odloženie hracej dosky pred vykonaním príkazu.
       * @var oldBoard_
       */
      GameBoard oldBoard_;

      /**
       * @brief Odloženie hráča, pred vykonaním príkazu.
       * @var oldCurrentPlayer_
       */
      int oldCurrentPlayer_;

      /**
       * @brief Odloženie súradníc pred ich zahraním.
       * @var oldCurrentMove_
       */
      std::pair<unsigned, unsigned> oldCurrentMove_;//nie coords lebo je to class

    public:
      /**
       * @brief Konštruktor pre príkaz hrania ťahu.
       * @param   g     referenica na aktuálnu instanciu MainGame
       * @param   x     x-súradnica aktuálneho ťahu
       * @param   y     y-súradnica aktuálneho ťahu
       */
      PlayMove(std::unique_ptr<MainGame> *g, unsigned x, unsigned y);

      /**
       * @brief Deštruktor príkazu hrania ťahu.
       * @method ~PlayMove
       */
      virtual ~PlayMove(){}

      /**
       * @brief Vykonanie príkazu hrania ťahu.
       * @method Execute
       * @return True ak vykonaný úspešne.
       */
      virtual bool Execute() override;

      /**
       * @brief Krok späť.
       * @method Undo
       */
      virtual void Undo() override;

      /**
       * @brief Krok vpred.
       * @method Redo
       */
      virtual void Redo() override;

      /**
       * @brief Ulož príkaz do súboru.
       * @method SaveToFile
       * @param  outF       otvorený popisovač súboru.
       */
      virtual void SaveToFile(std::ostream &outF) override;

  };
}

#endif
