/**
* @file
* @brief Správa hry.
* @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
* @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
*/

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
        int current_player_num_ = 0;
        // frozen stuff
    public:
        MainGame(unsigned size, PlayerType white, PlayerType black);

        bool Event(unsigned x, unsigned y); // event funkce

        const Player& GetCurrentPlayer() const { return *players_[current_player_num_]; }

        bool IsEnd() const;

        //void setLogic(GameLogic oldLogic) {logic_ = oldLogic;}

        bool CanPlay(Color color) const;

        const GameLogic& GetLogic() const { return logic_; }
        GameLogic& GetLogic() { return logic_; }

        const GameBoard& GetBoard() const {return logic_.GetBoard();}

        void SetNames(const std::pair<std::string, std::string>& names);

        std::pair<std::string, std::string> GetNames();

        bool SaveGameToFile(std::ofstream &thisFile);

        void SetCurrentPlayer(int n) {current_player_num_ = n;}

        //void setGameBoard(const std::vector<std::string> &GB){logic_.setGameBoard(GB);}
        void SetGameBoard(const std::vector<std::string> &){}

        int GetCurrentPlayerNum(){ return current_player_num_;}

        Coords TellAIToPlay();

    };
}


#endif //OTHELLO_MAINGAME_HH
