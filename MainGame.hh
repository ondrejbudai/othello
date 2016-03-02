//
// Created by ondra on 11.2.16.
//

#ifndef OTHELLO_MAINGAME_HH
#define OTHELLO_MAINGAME_HH

#include <memory>
#include "AI.hh"
#include "GameBoard.hh"
#include <fstream>

namespace othello {

    enum class PlayerType {
        HUMAN, AI
    };

    
    struct HistoryItem{
        std::vector<std::vector<Field>> board;
        Color currentPlayer;
        std::pair<unsigned, unsigned> currentMove;//nie coords lebo je to class
    };


    class MainGame {
    private:
        GameLogic logic_;
        std::vector<HistoryItem> history_;
        std::vector<std::unique_ptr<Player>> players_;
        int current_player_num = 0;
        bool isRunning_ = true;
        // frozen stuff
    public:
        MainGame(unsigned size, PlayerType white, PlayerType black);

        void event(unsigned x, unsigned y); // event funkce

        const Player& getCurrentPlayer() const { return *players_[current_player_num]; }

        void printGameBoard() const;//Zobrazi hraciu plochu na terminal

        bool isEnd() const;

        bool canPlay(Color color) const;

        const GameLogic& getLogic() const { return logic_; }

        bool IsRunning() const { return isRunning_; }

        void StopRunning(){ isRunning_ = false;}

        void setNames(const std::vector<std::string>& names);
        
        void printHistory() const ;
    
        bool saveHistoryToFile(std::ofstream &thisFile);
    };
}


#endif //OTHELLO_MAINGAME_HH
