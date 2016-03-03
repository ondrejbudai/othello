#include <QMessageBox>
#include <QFileDialog>
#include "OthelloGui.hh"
#include "ui_StartPanel.h"
#include "GraphicsScene.hh"
#include "StartPanel.hh"
#include <iostream>

//TODO ukladanie+nacitanie hry
//TODO DO DO ukoncenie hry

constexpr unsigned AI_TIMEOUT = 0;

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
        ui->gameBoardLayout->addWidget(startView);

        //TODO: move me
        infoPanel = new InfoPanel;
        startPanel = new StartPanel;
        ui->infoPanelLayout->addWidget(startPanel);

        connect(playerScreen, &PlayerSelection::on_ButtonStartGame_clicked, this, &OthelloGui::LoadGameConfiguration);
        connect(startPanel, &StartPanel::on_ButtonNewGame_clicked, this, &OthelloGui::ButtonNewGame);
        connect(startPanel, &StartPanel::on_ButtonLoadGame_clicked, this, &OthelloGui::ButtonLoadGame);

        timer = new QTimer();
        timer->setInterval(AI_TIMEOUT);
        timer->setSingleShot(true);

        connect(timer, &QTimer::timeout, this, &OthelloGui::TimeoutSlot);
    }

    //Po kliknuti na zaciatok hry spracuje nastavenia hry, ktore si uziatel zvolil
    void OthelloGui::LoadGameConfiguration(){

        //vektor na stiahnutie mien hracov
        std::array<QString, 2> names = playerScreen->getNames();
        //vektor na stiahnutie typu hracov
        std::array<QString, 2> types = playerScreen->getTypes();
        
        std::array<std::string, 2> namesStd;
        namesStd[0] = names[0].toStdString();
        namesStd[1] = names[1].toStdString();

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
        
        ShowGameBoard(p1, p2, boardSize, namesStd);
    }

    void OthelloGui::ShowGameBoard(PlayerType p1, PlayerType p2, unsigned boardSize, std::array<std::string, 2> names){
        
        //inicilizujeme hraciu dosku
        game_ = std::make_unique<MainGame>(boardSize, p2, p1);

        game_->setNames(names);

        const static QString s1{"<font size=5>"};
        const static QString s2{"</font>"};

        //names[0] = s1 + names[0] + s2;
        //names[1] = s1 + names[1] + s2;

        infoPanel->setNames(names);

        scene = new GraphicsScene(game_->getLogic().getBoard());

        connect(scene, &GraphicsScene::ClickSignal, this, &OthelloGui::GameClickSlot);
        view = new GraphicsView(scene);
        ui->gameBoardLayout->removeWidget(ui->gameBoardLayout->currentWidget());
        ui->gameBoardLayout->addWidget(view);

        ui->infoPanelLayout->removeWidget(ui->infoPanelLayout->currentWidget());
        ui->infoPanelLayout->addWidget(infoPanel);
        
        connect(infoPanel, &InfoPanel::on_ButtonSaveGame_clicked, this, &OthelloGui::ButtonSaveGame);

        repaintGame();
    }

    // v pravem sloupci, zobrazi obrazovku s vyberem hracu
    void OthelloGui::ButtonNewGame() {

        ui->gameBoardLayout->removeWidget(ui->gameBoardLayout->currentWidget());
        ui->gameBoardLayout->addWidget(playerScreen);
    }

    //umozni hracovi ulozit hru do suboru
    void OthelloGui::ButtonSaveGame() {
       
        //this is fu**ing awesome!
        QString fileName_ = QFileDialog::getSaveFileName(this, tr("Save File"), ".", "Text Files (*.txt)");
        
        std::string fileName = fileName_.toUtf8().constData();
        
        std::ofstream fl;
        fl.open(fileName);
        game_->saveGameToFile(fl);
        fl.close();
    }

    //nacita subor s ulozenou hrou a danu hru vytvori
    void OthelloGui::ButtonLoadGame() {
        QString fileName_ = QFileDialog::getOpenFileName(this, tr("Open File"), ".");

        // zkontroluj, zda hrac vybral nejaky soubor
        if (fileName_.isNull())
            return;

        std::string fileName = fileName_.toUtf8().constData();
        
        std::ifstream inF;
        inF.open(fileName);
        //nacitaj hlavicku 

        //vektor na stiahnutie mien hracov
        std::array<std::string, 2> names;
        //vektor na stiahnutie typu hracov
        std::array<std::string, 2> types;
        
        getline(inF, names[0]);
        getline(inF, types[0]);
        getline(inF, names[1]);
        getline(inF, types[1]);

        //Spracujeme hracov podla ich typu
        PlayerType p1;
        PlayerType p2;
        if (types[0] == "AI")
            p1 = PlayerType::AI;
        else
            p1 = PlayerType::HUMAN;
        if (types[1] == "AI")
            p2 = PlayerType::AI;
        else
            p2 = PlayerType::HUMAN;

        //precitame zvolenu velkost dosky a prekonvertujeme na int
        std::string boardSizeS;
        getline(inF, boardSizeS);
        int boardSize = std::stoi(boardSizeS);
        
        ShowGameBoard(p1, p2, boardSize, names);

        //nacitaj akruanu dosku
        //nacitaj historiu
        inF.close();
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

        // zkontroluj konec
        if (game_->isEnd()) {
            // do a lot of funny things
        }

        if (game_->getCurrentPlayer().isAi())
            timer->start();

    }
}

