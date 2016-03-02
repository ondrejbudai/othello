#ifndef OTHELLO_OTHELLOGUI_HH
#define OTHELLO_OTHELLOGUI_HH

#include <QGraphicsView>
#include "PlayerSelection.hh"
#include "MainGame.hh"
#include "InfoPanel.hh"
#include "GraphicsScene.hh"
#include "StartPanel.hh"

namespace Ui {
    class OthelloGui;
}

namespace othello {
    class OthelloGui : public QWidget {
    Q_OBJECT

    public slots:

        void ShowGameBoard();

        void EndOfGame();

        void ButtonNewGame();

        void ButtonSaveGame();

        void GameClickSlot(unsigned mx, unsigned my);

        void TimeoutSlot();

    private:
        Ui::OthelloGui* ui;
        std::unique_ptr<MainGame> game_;
        QGraphicsScene* startScene;
        QGraphicsView* startView;
        PlayerSelection* playerScreen;
        GraphicsScene* scene;
        QGraphicsView* view;
        InfoPanel* infoPanel;
        QTimer* timer;
        StartPanel* startPanel;

        void repaintGame();

    public:

        explicit OthelloGui(QWidget* parent = 0);

    };
}

#endif //OTHELLO_OTHELLOGUI_HH
