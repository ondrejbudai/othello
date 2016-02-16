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
std::vector<QString> PlayerSelection::getNames() {
    std::vector<QString> ret;
    ret.push_back(ui->name1->text());
    ret.push_back(ui->name2->text());
    return ret;
}
