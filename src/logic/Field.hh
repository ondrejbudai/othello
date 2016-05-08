/**
 * @file
 * @brief Jedno herní pole.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef OTHELLO_FIELD_HH
#define OTHELLO_FIELD_HH

namespace othello {
    /**
     * @brief Zoznam farieb hracov.
     * @enum Color
     */
    enum class Color {
        BLACK, WHITE
    };

    /**
     * @brief Jedno hracie políčko.
     * @class Field
     */
    class Field {
    private:
        /**
         * @brief True - Políčko je obsadené, inak voľné.
         * @var occupied_
         */
        bool occupied_;

        /**
         * @brief Farba hráča, ktorý má políčko obsadené.
         * @var piece_
         */
        Color piece_;

        /**
         * @brief Aktuány hráč sem môže položiť kameň.
         * @var possible_
         */
        bool possible_;
    public:
        /**
         * @brief Základný konštruktor na políčko, impicitne neobsadené.
         * @method Field
         */
        Field() : occupied_{false}, possible_(false){}

        /**
         * @brief Konšturktor na políčko, ktorý ho rovno obsadí.
         * @method Field
         * @param   piece   Farba hráča, pre ktorého sa inicializuje.
         */
        Field(Color piece) : occupied_{true}, piece_{piece}{}

        /**
         * @brief Vráti údaje o políčku.
         * @method GetStatus
         * @param  color     Naplní aktuálnou farbou.
         * @return           True ak obsadené, inak False.
         */
        bool GetStatus(Color& color) const;

        /**
         * @brief Vráti obsadenosť políčka.
         * @method IsOccupied
         * @return True ak obsadené, inak False.
         */
        bool IsOccupied() const {return occupied_;}

        /**
         * @brief Nastaví políčko pre hráča.
         * @method SetColor
         * @param  color    Farba hráča, ktorý si obsadzuje políčko.
         */
        void SetColor(Color color){piece_ = color; occupied_ = true;}

        /**
         * @brief Nastaví možnosť obsadené.
         * @method SetPossible
         * @param  to          Nová hodnota možnosti obsadené.
         */
        void SetPossible(bool to){possible_ = to;}

        /**
         * @brief Vráti hodnotu možnosti obsadené
         * @method IsPossible
         * @return Hodnota možnosti obsadené.
         */
        bool IsPossible() const {return possible_;}
    };
}

#endif
