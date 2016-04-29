#ifndef HISTORYITEMGUI_HH
#define HISTORYITEMGUI_HH

#include <QWidget>
#include "../logic/GameBoard.hh"
#include "ui_HistoryItemGui.h"

namespace othello{
    //namespace Ui {
    //class HistoryItemGui;
    //}

    class HistoryItemGui : public QWidget
    {
        Q_OBJECT

    public:
        explicit HistoryItemGui(QWidget *parent = 0);
        ~HistoryItemGui();
        void setColor(Color C);
        void setMove(std::pair<unsigned, unsigned> M);
        void setBoard(std::vector<std::vector<Field>> &B);

    private:
        Ui::HistoryItemGui ui;
    };
}
#endif // HISTORYITEMGUI_HH
