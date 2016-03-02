#include <QMessageBox>
#include "OthelloGui.hh"
#include "ui_OthelloGui.h"
#include "ui_StartPanel.h"
#include "GraphicsScene.hh"
#include "StartPanel.hh"
#include <iostream>

//TODO ukladanie+nacitanie hry
//TODO DO DO ukoncenie hry

namespace othello {
    class GraphicsView : public QGraphicsView {
    public:
        GraphicsView(QGraphicsScene* s) : QGraphicsView(s) { }

        virtual void resizeEvent(QResizeEvent*) {
            fitInView(0, 0, GAME_SIZE, GAME_SIZE, Qt::KeepAspectRatio);
            //dynamic_cast<GraphicsScene*>(scene())->setSize(event->size());
        }
    };

    OthelloGui::OthelloGui(QWidget* parent) : QWidget(parent), ui(new Ui::OthelloGui) {

        //iniciaizujeme UI
        ui->setupUi(this);

        //inicializujem si okno pre vyber hracov
        playerScreen = new PlayerSelection();

        //inicilziujeme a nastavime uvodnu obrazovku
        QImage image("img/startScreenImage.jpg");
        startScene = new QGraphicsScene();
        startView = new QGraphicsView(startScene);
        QGraphicsPixmapItem* startImage = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        startScene->addItem(startImage);
        ui->gameBoardLayout->layout()->addWidget(startView);

        infoPanel = new InfoPanel();
//        ui->infoPanelLayout->layout()->addWidget(infoPanel);


        startPanel = new StartPanel;
        ui->infoPanelLayout->layout()->addWidget(startPanel);

        connect(playerScreen, &PlayerSelection::on_ButtonStartGame_clicked, this, &OthelloGui::ShowGameBoard);
        //connect(infoPanel, &InfoPanel::on_ButtonNewGame_clicked, this, &OthelloGui::ButtonNewGame);

        connect(startPanel, &StartPanel::on_ButtonNewGame_clicked, this, &OthelloGui::ButtonNewGame);

        timer = new QTimer();
        timer->setInterval(1000);
        timer->setSingleShot(true);

        connect(timer, &QTimer::timeout, this, &OthelloGui::TimeoutSlot);
    }

    // reaguje na klik v lepevem sloupci, zobrazi herni desku
    void OthelloGui::ShowGameBoard(){
        //vektor na stiahnutie mien hracov
        std::array<QString, 2> names = playerScreen->getNames();
        //vektor na stiahnutie typu hracov
        std::array<QString, 2> types = playerScreen->getTypes();

        //Kontrola ci nie su prazdne mena
        const static QString emptyString{""};
        if (names[0] == emptyString || names[1] == emptyString){
            QMessageBox emptyPlayer;
            emptyPlayer.setText("Meno hraca nemoze byt prazdne");
            emptyPlayer.exec();
            return;
        }

        //Spracujeme hracov podla ich typu
        const static QString AI{"AI"};
        const static QString Human{"Human"};
        PlayerType p1;
        PlayerType p2;
        if (types[0] == AI)
            p1 = PlayerType::AI;
        else
            p1 = PlayerType::HUMAN;
        if (types[1] == AI)
            p2 = PlayerType::AI;
        else
            p2 = PlayerType::HUMAN;

        //precitame zvolenu velkost dosky a prekonvertujeme na int
        QString boardSizeS = playerScreen->getBoardSize();
        int boardSize = boardSizeS.toInt();

        
        //inicilizujeme hraciu dosku
        game_ = std::make_unique<MainGame>(boardSize, p2, p1);

        std::vector<std::string> namesStd{names[0].toStdString(), names[1].toStdString()};
        game_->setNames(namesStd);

        const static QString s1{"<font size=5>"};
        const static QString s2{"</font>"};

        names[0] = names[0].prepend(s1).append(s2);
        names[1] = names[1].prepend(s1).append(s2);

        infoPanel->setNames(names);

        scene = new GraphicsScene(game_->getLogic().getBoard());

        connect(scene, &GraphicsScene::ClickSignal, this, &OthelloGui::GameClickSlot);
        view = new GraphicsView(scene);

        ui->gameBoardLayout->layout()->removeWidget(playerScreen);
        ui->gameBoardLayout->layout()->addWidget(view);

        ui->infoPanelLayout->layout()->removeWidget(startPanel);
        startPanel->hide();
        
        ui->infoPanelLayout->layout()->addWidget(infoPanel);

        repaintGame();
    }


    void OthelloGui::EndOfGame(){
        game_->StopRunning();
        disconnect(scene,  SIGNAL(EndOfGame()), this, SLOT(EndOfGame()));
        //delete view;
        //delete scene;
        //game_.~MainGame();//sorry
        std::cout<<"SHOUDL END----------------------------\n"<<std::flush;
    }

    // v pravem sloupci, zobrazi obrazovku s vyberem hracu
    void OthelloGui::ButtonNewGame() {

        ui->gameBoardLayout->layout()->removeWidget(startView);
        ui->gameBoardLayout->layout()->addWidget(playerScreen);
    }

    void OthelloGui::GameClickSlot(unsigned mx, unsigned my) {
        // AI na tahu, nedelej nic
        if (game_->getCurrentPlayer().isAi())
            return;

        // update a prekreslit
        game_->event(mx, my);
        repaintGame();
    }

    void OthelloGui::TimeoutSlot() {
        game_->event(0, 0);
        repaintGame();
    }

    void OthelloGui::repaintGame() {
        scene->repaint();
        infoPanel->WriteScore(game_->getLogic().getScore());

        if (game_->getCurrentPlayer().isAi())
            timer->start();
    }
}

