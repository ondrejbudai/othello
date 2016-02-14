#include "PlayerSelection.hh"
#include "ui_PlayerSelection.h"

PlayerSelection::PlayerSelection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerSelection)
{
    ui->setupUi(this);
}

PlayerSelection::~PlayerSelection()
{
    delete ui;
}
/*
void PlayerSelection::on_ButtonStartGame_clicked()
{

}
*/
