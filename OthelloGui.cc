#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QtCore>
#include <iostream>
#include <QResizeEvent>
#include "OthelloGui.hh"
#include "MainGame.hh"
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

    //vykresli hraciu dosku
    void OthelloGui::ShowGameBoard(){
        //inicilizujeme hraciu dosku
        scene = new GraphicsScene(game_);
        view = new GraphicsView(scene);
        if (ui->ButtonNewGame->text() == QString("Reset Game"))
            std::cout<< "Sme v resete\n"<<std::endl; 
        
        ui->gameBoard->layout()->removeWidget(topFeature);
        ui->gameBoard->layout()->addWidget(view);
        topFeature = view;
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
        std::cout<<"SHOUDL END----------------------------\n"<<std::flush;
    } 
    
    //po staceni tlacitka Start Game
    void OthelloGui::on_ButtonNewGame_clicked(){
       

        ui->gameBoard->layout()->removeWidget(topFeature);
       
        //pridame pozadie 
        startScene->addItem(startImageLight);
        ui->gameBoard->layout()->addWidget(startViewLight);

        ui->gameBoard->layout()->update();
        //odoberieme ho
        ui->gameBoard->layout()->removeWidget(startViewLight);
        
        //a pridame tabulku
        ui->gameBoard->layout()->addWidget(playerScreen);
        topFeature = playerScreen;        
        //ShowGameBoard();
    }
    

    OthelloGui::OthelloGui(QWidget *parent): QWidget(parent), ui(new Ui::OthelloGui),
                    game_{10,PlayerType::AI,PlayerType::AI} {
        
        //iniciaizujeme UI 
        ui->setupUi(this);      
       
        //inicializujem si okno pre vyber hracov
        playerScreen = new PlayerSelection(); 

        //inicilziujeme a nastavime uvodnu obrazovku
        QImage image("img/startScreenImage.jpg");
        startScene = new QGraphicsScene();
        startView  = new QGraphicsView(startScene);
        QGraphicsPixmapItem *startImage  = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        startScene->addItem(startImage);
        ui->gameBoard->layout()->addWidget(startView);
        topFeature = startView;        
        
        //iniciliazujem svetlejsiu obrazovku 
        startSceneLight = new QGraphicsScene();
        startViewLight  = new QGraphicsView(startSceneLight);
        QImage imageLight("img/startScreenImageLight.jpg");
        startImageLight  = new QGraphicsPixmapItem(QPixmap::fromImage(imageLight));

        //inicialziujem hodinky


        connect(playerScreen , SIGNAL(on_ButtonStartGame_clicked()),this, SLOT(ShowGameBoard()));        
    }
}

