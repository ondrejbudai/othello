#include <QMessageBox>
#include <QFileDialog>
#include "OthelloGui.hh"
#include "EndScreen.hh"
#include <cassert>

constexpr unsigned AI_TIMEOUT = 1000;

namespace othello {

    void clearStackedWidget(QStackedWidget* widget) {
        QWidget* w = widget->currentWidget();
        if (!w)
            return;
        widget->removeWidget(w);
    }

    OthelloGui::OthelloGui(QWidget* parent) : QWidget(parent) {

        //iniciaizujeme UI
        ui.setupUi(this);

        //inicializujem si okno pre vyber hracov
        playerScreen = new PlayerSelection();

        //inicilziujeme a nastavime uvodnu obrazovku
        QImage image("img/startScreenImage.jpg");
        startScene = new QGraphicsScene();
        startView = new QGraphicsView(startScene);
        QGraphicsPixmapItem* startImage = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        startScene->addItem(startImage);
        ui.gameBoardLayout->addWidget(startView);

        startPanel = new StartPanel;
        ui.infoPanelLayout->addWidget(startPanel);

        connect(playerScreen, &PlayerSelection::on_ButtonStartGame_clicked, this, &OthelloGui::LoadGameConfiguration);
        connect(startPanel, &StartPanel::on_ButtonNewGame_clicked, this, &OthelloGui::ButtonNewGame);
        connect(startPanel, &StartPanel::on_ButtonLoadGame_clicked, this, &OthelloGui::ButtonLoadGame);

        timer = new QTimer();
        timer->setInterval(AI_TIMEOUT);
        timer->setSingleShot(true);

        connect(timer, &QTimer::timeout, this, &OthelloGui::TimeoutSlot);
    }

    void OthelloGui::PlayPause(){
      if (playAi){
        playAi = false;

      }
      else{
        playAi = true;
        repaintGame();

      }
    }

    //Po kliknuti na zaciatok hry spracuje nastavenia hry, ktore si uziatel zvolil
    void OthelloGui::LoadGameConfiguration(){

        //vektor na stiahnutie mien hracov
        std::array<QString, 2> names = playerScreen->getNames();
        //vektor na stiahnutie typu hracov
        std::array<QString, 2> types = playerScreen->getTypes();

        std::pair<std::string, std::string> namesStd{names[0].toStdString(), names[1].toStdString()};

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
        unsigned boardSize = boardSizeS.toUInt();

        ShowGameBoard(p1, p2, boardSize, namesStd);
    }

    void OthelloGui::ShowGameBoard(PlayerType p1, PlayerType p2, unsigned boardSize,
                                   const std::pair<std::string, std::string>& names) {

        //inicilizujeme hraciu dosku
        game_ = std::make_unique<MainGame>(boardSize, p2, p1);

        game_->SetNames(names);

        infoPanel = new InfoPanel;
        infoPanel->SetNames(names);

        scene = new BoardGraphics(*game_);

        connect(scene, &BoardGraphics::ClickSignal, this, &OthelloGui::GameClickSlot);
        view = new GraphicsView(scene);
        connect(view, &GraphicsView::mouseMoveSignal, scene, &BoardGraphics::mouseMoveSlot);
        connect(view, &GraphicsView::enterSignal, scene, &BoardGraphics::enterSlot);
        connect(view, &GraphicsView::leaveSignal, scene, &BoardGraphics::leaveSlot);

        clearStackedWidget(ui.gameBoardLayout);
        ui.gameBoardLayout->addWidget(view);

        clearStackedWidget(ui.infoPanelLayout);
        ui.infoPanelLayout->addWidget(infoPanel);

        connect(infoPanel, &InfoPanel::on_ButtonSaveGame_clicked, this, &OthelloGui::ButtonSaveGame);
        connect(infoPanel, &InfoPanel::on_ButtonREDO_clicked, this, &OthelloGui::ButtonREDO);
        connect(infoPanel, &InfoPanel::on_ButtonUNDO_clicked, this, &OthelloGui::ButtonUNDO);
        connect(infoPanel, &InfoPanel::on_PlayPause_clicked, this, &OthelloGui::PlayPause);
        //connect(this, &InfoPanel::changeIcon, infoPanel, &InfoPanel::changeIcon);
        //connect(this, SIGNAL(changeIcon(bool)), &InfoPanel, SLOT(changeIcon(bool)));

        repaintGame();
    }

    void OthelloGui::ButtonShowHistory(){
        historyPanel = new HistoryPanel();
        clearStackedWidget(ui.infoPanelLayout);
        ui.infoPanelLayout->addWidget(historyPanel);
        //historyPanel->AddHistory(game_->getHistory());
        connect(historyPanel, &HistoryPanel::on_ButtonCancle_clicked, this, &OthelloGui::ShowInfoPanel);
        //zavolaj nacitanie historie
    }

    void OthelloGui::ShowInfoPanel(){
        clearStackedWidget(ui.infoPanelLayout);
        ui.infoPanelLayout->addWidget(infoPanel);
    }


    // v pravem sloupci, zobrazi obrazovku s vyberem hracu
    void OthelloGui::ButtonNewGame() {

        clearStackedWidget(ui.gameBoardLayout);
        ui.gameBoardLayout->addWidget(playerScreen);
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


    void OthelloGui::ButtonUNDO() {
      cmd_.undo();
      playAi = false;
      repaintGame();
    }

    void OthelloGui::ButtonREDO() {
      cmd_.redo();
      playAi = false;
      repaintGame();
    }
    //TODO vsetko s histroiou do samotneho bloku!
    //nacita subor s ulozenou hrou a danu hru vytvori
    void OthelloGui::ButtonLoadGame() {
        //TODO kontrola ci je subor ok a teda assert-y prerobit na hlasku o chybnom subore
        QString fileName_ = QFileDialog::getOpenFileName(this, tr("Open File"), ".");

        // zkontroluj, zda hrac vybral nejaky soubor
        if (fileName_.isNull())
            return;

        std::string fileName = fileName_.toUtf8().constData();

        std::ifstream inF;
        inF.open(fileName);
        //nacitaj hlavicku

        //vektor na stiahnutie mien hracov
        std::pair<std::string, std::string> names;
        //vektor na stiahnutie typu hracov
        std::pair<std::string, std::string> types;

        getline(inF, names.first);
        getline(inF, types.first);
        getline(inF, names.second);
        getline(inF, types.second);

        //Spracujeme hracov podla ich typu
        PlayerType p1;
        PlayerType p2;
        if (types.first == "AI")
            p1 = PlayerType::AI;
        else
            p1 = PlayerType::HUMAN;
        if (types.second == "AI")
            p2 = PlayerType::AI;
        else
            p2 = PlayerType::HUMAN;

        //precitame zvolenu velkost dosky a prekonvertujeme na int
        std::string boardSizeS;
        getline(inF, boardSizeS);
        unsigned boardSize = static_cast<unsigned>(std::stoi(boardSizeS));

        ShowGameBoard(p1, p2, boardSize, names);

        std::string oneLine;
        int currentPlayer;
        getline(inF, oneLine);
        currentPlayer = std::stoi(oneLine);
        game_->setCurrentPlayer(currentPlayer);

        //nacitaj aktualnu dosku
        getline(inF, oneLine);//precitam prazdny riadok
        std::vector<std::string> gameB;
        for (unsigned i = 0; i < boardSize; i++) {
            assert(!inF.eof());
            getline(inF, oneLine);
            assert(oneLine.length() == boardSize);
            gameB.push_back(oneLine);
        }
        assert(gameB.size() == boardSize);
        //game_->setGameBoard(gameB);
        getline(inF, oneLine);//empty
        getline(inF, oneLine);//HISTORY
        getline(inF, oneLine);//empty

        //a nacitame celu historiu
        // while (!inF.eof()){
        //     gameB.clear();
        //     HistoryItem newItem;
        //     getline(inF, oneLine);//nacitam kto hra
        //     if (oneLine == "")
        //         break;
        //     newItem.currentPlayer = (oneLine == "black" ? Color::BLACK : Color::WHITE);
        //     getline(inF, oneLine);//nacitam x
        //     newItem.currentMove.first = stoi(oneLine);
        //     getline(inF, oneLine);//nacitam y
        //     newItem.currentMove.second = stoi(oneLine);
        //
        //     for (unsigned i = 0; i < boardSize; i++) {
        //         assert(!inF.eof());
        //         getline(inF, oneLine);
        //         assert(oneLine.length() == boardSize);
        //         newItem.board.emplace_back();
        //         for (unsigned i = 0; i < oneLine.length(); ++i){
        //             Field n;
        //             if (oneLine[i] == '0')
        //                 n.occupied_ = false;
        //             else if (oneLine[i] == '1'){
        //                 n.occupied_ = true;
        //                 n.piece_ = Color::BLACK;
        //             } else if (oneLine[i] == '2'){
        //                 n.occupied_ = true;
        //                 n.piece_ = Color::WHITE;
        //             } else
        //                 assert(false);
        //             newItem.board.back().push_back(n);
        //         }
        //     }
            //game_->addToHistory(newItem);

            //TODO pridaj board a vloz do hitorie
            //TODO vloz do historie
        //}

        inF.close();
        repaintGame();
    }


    void OthelloGui::GameClickSlot(unsigned mx, unsigned my) {
        // AI na tahu, nedelej nic
        if (game_->getCurrentPlayer().isAi())
            return;
        else
          playAi = true;

        // update a prekreslit
        std::shared_ptr<ICommand> c(new PlayMove(&game_, mx, my));
        cmd_.execute(c);
        //game_->event(mx, my);
        repaintGame();
    }

    void OthelloGui::TimeoutSlot() {
        Coords coor = game_->TellAIToPlay();
        std::shared_ptr<ICommand> c(new PlayMove(&game_, coor.GetX(), coor.GetY()));
        cmd_.execute(c);
        //game_->event(0, 0);
        repaintGame();
    }

    void OthelloGui::repaintGame() {
        scene->repaint();
        infoPanel->WriteScore(game_->getLogic().getScore());
        infoPanel->HighlightPlayer(game_->getCurrentPlayer().getColor());

        // zkontroluj konec
        if (game_->isEnd()) {
            endGame();
            return;
        }

        if (playAi && game_->getCurrentPlayer().isAi())
            timer->start();

    }

    void OthelloGui::endGame() {
        clearStackedWidget(ui.gameBoardLayout);
        clearStackedWidget(ui.infoPanelLayout);

        EndScreen* end = new EndScreen;
        end->SetNames(game_->GetNames());
        end->SetScores(game_->getLogic().getScore());

        ui.infoPanelLayout->addWidget(startPanel);
        ui.gameBoardLayout->addWidget(end);

        game_ = nullptr;

    }
}
