/**
 * @file
 * @brief Jedno herní pole.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

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
