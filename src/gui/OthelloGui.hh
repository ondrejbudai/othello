#ifndef OTHELLO_OTHELLOGUI_HH
#define OTHELLO_OTHELLOGUI_HH

#include <QGraphicsView>
#include "PlayerSelection.hh"
#include "../logic/MainGame.hh"
#include "InfoPanel.hh"
#include "BoardGraphics.hh"
#include "StartPanel.hh"
#include "HistoryPanel.hh"
#include "ui_OthelloGui.h"
#include "../logic/commandManager.hh"

namespace othello {
    class OthelloGui : public QWidget {
    Q_OBJECT

    public slots:

        void LoadGameConfiguration();

        void ButtonNewGame();

        void ButtonSaveGame();

        void ButtonLoadGame();

        void ButtonShowHistory();

        void PlayPause();

        void ButtonREDO();

        void ButtonUNDO();

        void ShowInfoPanel();

        void GameClickSlot(unsigned mx, unsigned my);

        void TimeoutSlot();

    signals:
      void changeIcon(); 

    private:
        Ui::OthelloGui ui;
        std::unique_ptr<MainGame> game_;
        CommandManager cmd_;
        QGraphicsScene* startScene;
        QGraphicsView* startView;
        PlayerSelection* playerScreen;
        BoardGraphics* scene;
        GraphicsView* view;
        InfoPanel* infoPanel;
        HistoryPanel *historyPanel;
        QTimer* timer;
        StartPanel* startPanel;
        bool playAi = true;

        void ShowGameBoard(PlayerType p1, PlayerType p2, unsigned boardSize,
                           const std::pair<std::string, std::string>& names);
        void repaintGame();

        void endGame();

    public:

        explicit OthelloGui(QWidget* parent = 0);

    };
}

#endif //OTHELLO_OTHELLOGUI_HH
