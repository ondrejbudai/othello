/**
 * @file
 * @brief Jedno herní pole.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_FIELD_HH
#define OTHELLO_FIELD_HH

namespace othello {

    enum class Color {
        BLACK, WHITE
    };

    class Field {
    private:
        bool occupied_;
        Color piece_;
    public:
        Field() : occupied_{false}{}
        Field(Color piece) : occupied_{true}, piece_{piece}{}
        bool GetStatus(Color& color) const;
        bool IsOccupied() const {return occupied_;}
        void SetColor(Color color){piece_ = color; occupied_ = true;}
    };
}

#endif
