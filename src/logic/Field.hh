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
        bool SetColor(Color color){piece_ = color; occupied_ = true;}
    };
}
