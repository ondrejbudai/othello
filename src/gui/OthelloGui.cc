/**
 * @file
 * @brief Widget obsahující jednu instanci hry.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

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
        ui_.setupUi(this);

        //inicializujeme si okno pro vyber hracu
        player_screen_ = new PlayerSelection();

        //inicializujeme a nastavime uvodnu obrazovku
        QImage image("img/startScreenImage.jpg");
        start_scene_ = new QGraphicsScene();
        start_view_ = new QGraphicsView(start_scene_);
        QGraphicsPixmapItem* startImage = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        start_scene_->addItem(startImage);
        ui_.gameBoardLayout->addWidget(start_view_);

        // přídáme start panel
        start_panel_ = new StartPanel;
        ui_.infoPanelLayout->addWidget(start_panel_);

        // signály
        connect(player_screen_, &PlayerSelection::on_ButtonStartGame_clicked, this, &OthelloGui::LoadGameConfiguration);
        connect(start_panel_, &StartPanel::on_ButtonNewGame_clicked, this, &OthelloGui::ButtonNewGame);
        connect(start_panel_, &StartPanel::on_ButtonLoadGame_clicked, this, &OthelloGui::ButtonLoadGame);

        // nastavení Timeru pro AI
        timer_ = new QTimer();
        timer_->setInterval(AI_TIMEOUT);
        timer_->setSingleShot(true);

        connect(timer_, &QTimer::timeout, this, &OthelloGui::TimeoutSlot);
    }

    void OthelloGui::PlayPause(){
      if (play_ai_){
        play_ai_ = false;
        info_panel_->ChangeIcon(play_ai_);
      }
      else{
        play_ai_ = true;
        info_panel_->ChangeIcon(play_ai_);
        RepaintGame();
      }
    }

    //Po kliknuti na zaciatok hry spracuje nastavenia hry, ktore si uziatel zvolil
    void OthelloGui::LoadGameConfiguration(){

        //vektor na stiahnutie mien hracov
        std::pair<QString, QString> names = player_screen_->GetNames();
        //vektor na stiahnutie typu hracov
        std::pair<QString, QString> types = player_screen_->GetTypes();

        std::pair<std::string, std::string> namesStd{names.first.toStdString(), names.second.toStdString()};

        //Kontrola ci nie su prazdne mena
        const static QString emptyString{""};
        if (names.first == emptyString || names.second == emptyString){
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
        if (types.first == AI)
            p1 = PlayerType::AI;
        else
            p1 = PlayerType::HUMAN;
        if (types.second == AI)
            p2 = PlayerType::AI;
        else
            p2 = PlayerType::HUMAN;

        //precitame zvolenu velkost dosky a prekonvertujeme na int
        QString boardSizeS = player_screen_->GetBoardSize();
        unsigned boardSize = boardSizeS.toUInt();

        ShowGameBoard(p1, p2, boardSize, namesStd);
    }

    void OthelloGui::ShowGameBoard(PlayerType p1, PlayerType p2, unsigned boardSize,
                                   const std::pair<std::string, std::string>& names) {

        //inicilizujeme hraciu dosku
        game_ = std::make_unique<MainGame>(boardSize, p2, p1);
        game_->SetNames(names);

        // přidáme InfoPanel
        info_panel_ = new InfoPanel;
        info_panel_->SetNames(names);
        clearStackedWidget(ui_.infoPanelLayout);
        ui_.infoPanelLayout->addWidget(info_panel_);

        // propojíme signály
        connect(info_panel_, &InfoPanel::on_ButtonSaveGame_clicked, this, &OthelloGui::ButtonSaveGame);
        connect(info_panel_, &InfoPanel::on_ButtonREDO_clicked, this, &OthelloGui::ButtonREDO);
        connect(info_panel_, &InfoPanel::on_ButtonUNDO_clicked, this, &OthelloGui::ButtonUNDO);
        connect(info_panel_, &InfoPanel::on_PlayPause_clicked, this, &OthelloGui::PlayPause);

        // přidáme herní obrazovku
        scene_ = new BoardGraphics(*game_);
        view_ = new GraphicsView(scene_);
        clearStackedWidget(ui_.gameBoardLayout);
        ui_.gameBoardLayout->addWidget(view_);

        // popropojujeme signály
        connect(scene_, &BoardGraphics::ClickSignal, this, &OthelloGui::GameClickSlot);
        connect(view_, &GraphicsView::MouseMoveSignal, scene_, &BoardGraphics::MouseMoveSlot);
        connect(view_, &GraphicsView::EnterSignal, scene_, &BoardGraphics::EnterSlot);
        connect(view_, &GraphicsView::LeaveSignal, scene_, &BoardGraphics::LeaveSlot);



        RepaintGame();
    }


    void OthelloGui::ShowInfoPanel(){
        clearStackedWidget(ui_.infoPanelLayout);
        ui_.infoPanelLayout->addWidget(info_panel_);
    }


    // v pravem sloupci, zobrazi obrazovku s vyberem hracu
    void OthelloGui::ButtonNewGame() {

        clearStackedWidget(ui_.gameBoardLayout);
        ui_.gameBoardLayout->addWidget(player_screen_);
    }

    //umozni hracovi ulozit hru do suboru
    void OthelloGui::ButtonSaveGame() {

        // toto je krásné
        QString fileName_ = QFileDialog::getSaveFileName(this, tr("Save File"), ".", "Text Files (*.txt)");

        std::string fileName = fileName_.toUtf8().constData();

        std::ofstream fl;
        fl.open(fileName);
        game_->SaveGameToFile(fl);
        cmd_.SaveToFile(fl);
        fl.close();
    }


    void OthelloGui::ButtonUNDO() {
      cmd_.Undo();
      play_ai_ = false;
      info_panel_->ChangeIcon(play_ai_);
      RepaintGame();
    }

    void OthelloGui::ButtonREDO() {
      cmd_.Redo();
      play_ai_ = false;
      info_panel_->ChangeIcon(play_ai_);
      RepaintGame();
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
        //Nastav ze zo suboru sa hra a zacni hrat

        int count;
        inF>>count;

        int mx;
        int my;
        for (int i = 0; i < count; i++){
          inF>>mx;
          inF>>my;
          std::shared_ptr<ICommand> c(new PlayMove(&game_, mx, my));
          cmd_.Execute(c);
        }
        inF.close();
        RepaintGame();
    }


    void OthelloGui::GameClickSlot(unsigned mx, unsigned my) {
        // AI na tahu, nedelej nic
        if (game_->GetCurrentPlayer().IsAi())
            return;
        else{
          play_ai_ = true;
          info_panel_->ChangeIcon(play_ai_);
        }

        // update a prekreslit
        std::shared_ptr<ICommand> c(new PlayMove(&game_, mx, my));
        cmd_.Execute(c);
        //game_->event(mx, my);
        RepaintGame();
    }

    void OthelloGui::TimeoutSlot() {
        Coords coor = game_->TellAIToPlay();
        std::shared_ptr<ICommand> c(new PlayMove(&game_, coor.GetX(), coor.GetY()));
        cmd_.Execute(c);
        //game_->event(0, 0);
        RepaintGame();
    }

    void OthelloGui::RepaintGame() {
        scene_->Repaint();
        info_panel_->WriteScore(game_->GetLogic().GetScore());
        info_panel_->HighlightPlayer(game_->GetCurrentPlayer().GetColor());

        // zkontroluj konec
        if (game_->IsEnd()) {
            EndGame();
            return;
        }

        if (play_ai_ && game_->GetCurrentPlayer().IsAi())
            timer_->start();

    }

    void OthelloGui::EndGame() {
        clearStackedWidget(ui_.gameBoardLayout);
        clearStackedWidget(ui_.infoPanelLayout);

        EndScreen* end = new EndScreen;
        end->SetNames(game_->GetNames());
        end->SetScores(game_->GetLogic().GetScore());

        ui_.infoPanelLayout->addWidget(start_panel_);
        ui_.gameBoardLayout->addWidget(end);

        game_ = nullptr;

    }
}
