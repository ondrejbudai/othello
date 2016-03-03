#ifndef OTHELLO_INFOPANEL_HH
#define OTHELLO_INFOPANEL_HH

#include <QWidget>
#include <QFrame>
#include <string>
#include "ui_InfoPanel.h"
#include "GameBoard.hh" 

namespace othello {
    class InfoPanel : public QFrame {
    Q_OBJECT

    private:
        Ui::InfoPanel* ui;

    public:

        explicit InfoPanel(QWidget* parent = 0);

        void WriteScore(std::pair<unsigned, unsigned> score);

        void SetNames(const std::pair<std::string, std::string>& names);

        void HighlightPlayer(Color c);
    signals:
        void on_ButtonSaveGame_clicked();
        
    };
}

#endif //OTHELLO_INFOPANEL_HH
