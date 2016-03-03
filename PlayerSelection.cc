#include "PlayerSelection.hh"

PlayerSelection::PlayerSelection(QWidget *parent) :
        QFrame(parent),
        ui(new Ui::PlayerSelection)
{
    ui->setupUi(this);

    //nastavime aby prvy hrac bol defaulte Human a druhy AI
    ui->selectPlayer1->setCurrentIndex(0);
    ui->selectPlayer2->setCurrentIndex(1);

    //nastavime defaulte velkost hracej plochy na 8
    ui->BoardSize->setCurrentIndex(1);

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


std::array<QString, 2> PlayerSelection::getNames() {
    return {ui->name1->text(), ui->name2->text()};
}

std::array<QString, 2> PlayerSelection::getTypes() {
    return {ui->selectPlayer1->currentText(), ui->selectPlayer2->currentText()};
}
