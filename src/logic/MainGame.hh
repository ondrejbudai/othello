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

    class MainGame {
    private:
        GameLogic logic_;
        std::vector<std::unique_ptr<Player>> players_;
        int current_player_num = 0;
        // frozen stuff
    public:
        MainGame(unsigned size, PlayerType white, PlayerType black);

        void event(unsigned x, unsigned y); // event funkce

        const Player& getCurrentPlayer() const { return *players_[current_player_num]; }

        void printGameBoard() const;//Zobrazi hraciu plochu na terminal

        bool isEnd() const;

        //void setLogic(GameLogic oldLogic) {logic_ = oldLogic;}

        bool canPlay(Color color) const;

        const GameLogic& getLogic() const { return logic_; }

        GameLogic& getLogicRef() { return logic_; }

        void SetNames(const std::pair<std::string, std::string>& names);

        std::pair<std::string, std::string> GetNames();

        void printHistory() const ;

        bool saveGameToFile(std::ofstream &thisFile);

        void setCurrentPlayer(int n) {current_player_num = n;}

        //void setGameBoard(const std::vector<std::string> &GB){logic_.setGameBoard(GB);}
        void setGameBoard(const std::vector<std::string> &GB){}

        //std::vector<HistoryItem> getHistory()const { return history_;}

        //void addToHistory(HistoryItem n);

        int getCurrentPlayerNum(){ return current_player_num;}

        Coords TellAIToPlay();

    };
}


#endif //OTHELLO_MAINGAME_HH
