/**
* @file
* @brief Definice abstraktního hráče.
* @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
* @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
*/

#ifndef OTHELLO_PLAYER_HH
#define OTHELLO_PLAYER_HH

#include<string>
#include "GameLogic.hh"

namespace othello {

    class Player {
    protected:
        Color color_;
        std::string name_;
        const GameLogic& logic_;
    public:
        Player(Color c, const GameLogic& logic) : color_{c}, logic_{logic} { }

        virtual ~Player(){}

        virtual Coords Play() { return {0, 0}; }

        virtual Color GetColor() const { return color_; }

        virtual bool IsAi() const { return false; }

        void SetName(std::string name) { name_ = name; }

        std::string GetName() {return name_;}
    };
}

#endif //OTHELLO_PLAYER_HH
