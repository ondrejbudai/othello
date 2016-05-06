/**
 * @file
 * @brief Widget na vybírání hráčů.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#include "PlayerSelection.hh"

PlayerSelection::PlayerSelection(QWidget *parent) :
        QFrame(parent),
        ui(new Ui::PlayerSelection)
{
    ui->setupUi(this);

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
