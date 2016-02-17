#include "PlayerSelection.hh"
#include "ui_PlayerSelection.h"

PlayerSelection::PlayerSelection(QWidget *parent) :
        QFrame(parent),
        ui(new Ui::PlayerSelection)
{
    //TODO nech sa nastavi hrac 2 ako AI a size na 8 (nechcem to ansilu posuvat, vyzera to blbo...
    ui->setupUi(this);
    setStyleSheet("background-image: url(./img/startScreenImageLight.jpg)"); 
    ui->name1->setText("Player 1");
    ui->name2->setText("Player 2");
    connect(ui->name1, SIGNAL(textChanged(const QString &)), ui->player1L, SLOT(setText(const QString &)));
    connect(ui->name2, SIGNAL(textChanged(const QString &)), ui->player2L, SLOT(setText(const QString &)));


}

PlayerSelection::~PlayerSelection()
{
    delete ui;
}

QString PlayerSelection::getBoardSize(){
    return (ui->BoardSize->currentText());
}


std::vector<QString> PlayerSelection::getNames() {
    //TODO kontrola ci nie je meno prazdne
    std::vector<QString> ret;
    ret.push_back(ui->name1->text());
    ret.push_back(ui->name2->text());
    return ret;
}

std::vector<QString> PlayerSelection::getTypes() {
    std::vector<QString> ret;
    ret.push_back(ui->selectPlayer1->currentText());
    ret.push_back(ui->selectPlayer2->currentText());
    return ret;
}
