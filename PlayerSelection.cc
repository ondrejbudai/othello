#include "PlayerSelection.hh"
#include "ui_PlayerSelection.h"

PlayerSelection::PlayerSelection(QWidget *parent) :
        QFrame(parent),
        ui(new Ui::PlayerSelection)
{
    ui->setupUi(this);
    setStyleSheet("background-image: url(./img/startScreenImageLight.jpg)");
}

PlayerSelection::~PlayerSelection()
{
    delete ui;
}
/*
void PlayerSelection::on_ButtonStartGame_clicked()
{

}*/
