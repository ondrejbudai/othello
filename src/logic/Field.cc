#include "Field.hh"

namespace othello {
    bool Field::GetStatus(Color& color) const {
        if(!occupied_){
            return false;
        }

        color = piece_;
        return true;
    }
}
