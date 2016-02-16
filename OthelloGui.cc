#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QtCore>
#include <iostream>
#include <QResizeEvent>
#include "OthelloGui.hh"
#include "ui_OthelloGui.h"
#include "PlayerSelection.hh"
#include "GraphicsScene.hh"

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
        ui->gameBoard->layout()->addWidget(startView);

        connect(playerScreen, SIGNAL(on_ButtonStartGame_clicked()), this, SLOT(ShowGameBoard()));
    }

    // reaguje na klik v lepevem sloupci, zobrazi herni desku
    void OthelloGui::ShowGameBoard(){
        //inicilizujeme hraciu dosku
        game_ = std::make_unique<MainGame>(10, PlayerType::HUMAN, PlayerType::AI);
        scene = new GraphicsScene(*game_);
        view = new GraphicsView(scene);
        if (ui->ButtonNewGame->text() == QString("Reset Game"))
            std::cout<< "Sme v resete\n"<<std::endl;

        ui->gameBoard->layout()->removeWidget(playerScreen);
        ui->gameBoard->layout()->addWidget(view);
        ui->ButtonNewGame->setText("Reset Game"); 
        
        connect(scene , SIGNAL(Score_Changed(int, int)),this, SLOT(WriteScore(int, int)));        
        connect(scene,  SIGNAL(EndOfGame()), this, SLOT(EndOfGame()));
    }

    void OthelloGui::WriteScore(int black, int white){
        QString sb = QString::number(black);
        ui->BlackScoreLabel->setText(sb);
        QString sw = QString::number(white);
        ui->WhiteScoreLabel->setText(sw);
    }

    void OthelloGui::EndOfGame(){
        game_->StopRunning();
        disconnect(scene , SIGNAL(Score_Changed(int, int)),this, SLOT(WriteScore(int, int)));        
        disconnect(scene,  SIGNAL(EndOfGame()), this, SLOT(EndOfGame()));
        //delete view;
        //delete scene;
        //game_.~MainGame();//sorry
        std::cout<<"SHOUDL END----------------------------\n"<<std::flush;
    }

    // v pravem sloupci, zobrazi obrazovku s vyberem hracu
    void OthelloGui::on_ButtonNewGame_clicked() {


        ui->gameBoard->layout()->removeWidget(startView);

        ui->gameBoard->layout()->addWidget(playerScreen);
    }
}

